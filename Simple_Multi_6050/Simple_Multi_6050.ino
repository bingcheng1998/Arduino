#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#define OUTPUT_READABLE_YAWPITCHROLL //输出数字
//#define OUTPUT_TEAPOT  //输出processing可接受的字符

#define INTERRUPT_PIN 2 
#define LED_PIN 13 

#define MPUNUM 3

#define AD01 7
#define AD02 8
#define AD03 9


bool blinkState = false;

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };


MPU6050 mpu;
MPU6050 mpu1;
MPU6050 mpu2;
//MPU6050 mpu(0x69); // <-- use for AD0 high

//------------------------------------------mpu-----------------------------------------------
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
//-----------------------------------------mpu1------------------------------------------------
// MPU control/status vars
bool dmpReady1 = false;  // set true if DMP init was successful
uint8_t mpuIntStatus1;   // holds actual interrupt status byte from MPU
uint8_t devStatus1;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize1;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount1;     // count of all bytes currently in FIFO
uint8_t fifoBuffer1[64]; // FIFO storage buffer

//-----------------------------------------mpu2------------------------------------------------
// MPU control/status vars
bool dmpReady2 = false;  // set true if DMP init was successful
uint8_t mpuIntStatus2;   // holds actual interrupt status byte from MPU
uint8_t devStatus2;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize2;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount2;     // count of all bytes currently in FIFO
uint8_t fifoBuffer2[64]; // FIFO storage buffer




void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    pinMode(INTERRUPT_PIN, INPUT);
    pinMode(AD01, OUTPUT);
    pinMode(AD02, OUTPUT);
    pinMode(AD03, OUTPUT);
    // initialize device
    Serial.println(F("Initializing I2C devices..."));

//-----------------------------------------------------------------------------------------
    
    mpu.initialize();
    digitalWrite(AD01, LOW);
    digitalWrite(AD02, HIGH);
    digitalWrite(AD03, HIGH);
    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // wait for ready
    //Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    //while (Serial.available() && Serial.read()); // empty buffer
    //while (!Serial.available());                 // wait for data
    //while (Serial.available() && Serial.read()); // empty buffer again

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));

    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);


        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        Serial.print(F("DMP Initialization failed:  "));
        if(devStatus == 1){
            Serial.println(F("initial memory load failed"));
        }
        else if(devStatus == 2){
            Serial.print(F("DMP configuration updates failed"));
        }
    }

//-----------------------------------------------------------------------------------------
    digitalWrite(AD01, HIGH);
    digitalWrite(AD02, LOW);
    digitalWrite(AD03, HIGH);
    mpu1.initialize();
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu1.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    Serial.println(F("Initializing DMP..."));
    devStatus1 = mpu1.dmpInitialize();
    mpu.setXAccelOffset(-4271);
    mpu.setYAccelOffset(269);
    mpu.setZAccelOffset(967); 
    mpu.setXGyroOffset(71);
    mpu.setYGyroOffset(-13);
    mpu.setZGyroOffset(-96);

    if (devStatus1 == 0) {
        Serial.println(F("Enabling DMP..."));
        mpu1.setDMPEnabled(true);
        mpuIntStatus1 = mpu1.getIntStatus();
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady1 = true;
        packetSize1 = mpu1.dmpGetFIFOPacketSize();
    } else {
        Serial.print(F("DMP Initialization failed:  "));
        if(devStatus1 == 1){
            Serial.println(F("initial memory load failed"));
        }
        else if(devStatus1 == 2){
            Serial.print(F("DMP configuration updates failed"));
        }
    }

//-----------------------------------------------------------------------------------------
    digitalWrite(AD01, HIGH);
    digitalWrite(AD02, HIGH);
    digitalWrite(AD03, LOW);
    mpu2.initialize();
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu2.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    Serial.println(F("Initializing DMP..."));
    devStatus2 = mpu2.dmpInitialize();
    mpu2.setXGyroOffset(220);
    mpu2.setYGyroOffset(76);
    mpu2.setZGyroOffset(-85);
    mpu2.setZAccelOffset(1788); 

    if (devStatus2 == 0) {
        Serial.println(F("Enabling DMP..."));
        mpu2.setDMPEnabled(true);
        mpuIntStatus2 = mpu2.getIntStatus();
        Serial.println(F("DMP2 ready! Waiting for first interrupt..."));
        dmpReady2 = true;
        packetSize2 = mpu2.dmpGetFIFOPacketSize();
    } else {
        Serial.print(F("DMP2 Initialization failed:  "));
        if(devStatus2 == 1){
            Serial.println(F("initial memory load failed"));
        }
        else if(devStatus2 == 2){
            Serial.print(F("DMP configuration updates failed"));
        }
    }
//-----------------------------------------------------------------------------------------
//    mpu.initialize();
//    Serial.println(F("Testing device connections..."));
//    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
//    Serial.println(F("Initializing DMP..."));
//    devStatus = mpu.dmpInitialize();
//    mpu.setXGyroOffset(220);
//    mpu.setYGyroOffset(76);
//    mpu.setZGyroOffset(-85);
//    mpu.setXAccelOffset(1788); 
//    mpu.setYAccelOffset(1788); 
//    mpu.setZAccelOffset(1788); 
//
//    if (devStatus == 0) {
//        Serial.println(F("Enabling DMP..."));
//        mpu.setDMPEnabled(true);
//        mpuIntStatus = mpu.getIntStatus();
//        Serial.println(F("DMP ready! Waiting for first interrupt..."));
//        dmpReady = true;
//        packetSize = mpu.dmpGetFIFOPacketSize();
//    } else {
//        Serial.print(F("DMP Initialization failed:  "));
//        if(devStatus == 1){
//            Serial.println(F("initial memory load failed"));
//        }
//        else if(devStatus == 2){
//            Serial.print(F("DMP configuration updates failed"));
//        }
//    }
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
    // configure LED for output
    pinMode(LED_PIN, OUTPUT);
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;
    else if (!dmpReady1) return;
    else if (!dmpReady2) return;

    // wait for MPU interrupt or extra packet(s) available
//    while (!mpuInterrupt && fifoCount < packetSize) {
//        // other program behavior stuff here
//        // .
//        // .
//        // .
//        // if you are really paranoid you can frequently test in between other
//        // stuff to see if mpuInterrupt is true, and if so, "break;" from the
//        // while() loop to immediately process the MPU data
//        // .
//        // .
//        // .
//    }

    // reset interrupt flag and get INT_STATUS byte
    
//-----------------------------------------------------------------------------------------
    //Serial.print(F("---A---"));
    digitalWrite(AD01, LOW);
    digitalWrite(AD02, HIGH);
    digitalWrite(AD03, HIGH);
//    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();
    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr0\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[2] * 180/M_PI);
            Serial.print("\t");
        #endif

    
        #ifdef OUTPUT_TEAPOT
            // display quaternion values in InvenSense Teapot demo format:
            teapotPacket[2] = fifoBuffer[0];
            teapotPacket[3] = fifoBuffer[1];
            teapotPacket[4] = fifoBuffer[4];
            teapotPacket[5] = fifoBuffer[5];
            teapotPacket[6] = fifoBuffer[8];
            teapotPacket[7] = fifoBuffer[9];
            teapotPacket[8] = fifoBuffer[12];
            teapotPacket[9] = fifoBuffer[13];
            Serial.write(teapotPacket, 14);
            teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
        #endif

        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }

//-----------------------------------------------------------------------------------------
    //Serial.print(F("---B---"));
    digitalWrite(AD01, HIGH);
    digitalWrite(AD02, LOW);
    digitalWrite(AD03, HIGH);
    mpuIntStatus1 = mpu1.getIntStatus();

    // get current FIFO count
    fifoCount1 = mpu1.getFIFOCount();
    if ((mpuIntStatus1 & 0x10) || fifoCount1 == 1024) {
        // reset so we can continue cleanly
        mpu1.resetFIFO();
        Serial.println(F("FIFO_1 overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus1 & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount1 < packetSize1) fifoCount1 = mpu1.getFIFOCount();

        // read a packet from FIFO
        mpu1.getFIFOBytes(fifoBuffer1, packetSize1);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount1 -= packetSize1;

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu1.dmpGetQuaternion(&q, fifoBuffer1);
            mpu1.dmpGetGravity(&gravity, &q);
            mpu1.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr1\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[2] * 180/M_PI);
            Serial.print("\t");
        #endif

    
        #ifdef OUTPUT_TEAPOT
            // display quaternion values in InvenSense Teapot demo format:
            teapotPacket[2] = fifoBuffer1[0];
            teapotPacket[3] = fifoBuffer1[1];
            teapotPacket[4] = fifoBuffer1[4];
            teapotPacket[5] = fifoBuffer1[5];
            teapotPacket[6] = fifoBuffer1[8];
            teapotPacket[7] = fifoBuffer1[9];
            teapotPacket[8] = fifoBuffer1[12];
            teapotPacket[9] = fifoBuffer1[13];
            Serial.write(teapotPacket, 14);
            teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
        #endif

        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }

    //-----------------------------------------------------------------------------------------
    //Serial.print(F("---C---"));
    digitalWrite(AD01, HIGH);
    digitalWrite(AD02, HIGH);
    digitalWrite(AD03, LOW);
    mpuIntStatus2 = mpu2.getIntStatus();

    // get current FIFO count
    fifoCount2 = mpu2.getFIFOCount();
    if ((mpuIntStatus2 & 0x10) || fifoCount2 == 1024) {
        // reset so we can continue cleanly
        mpu2.resetFIFO();
        Serial.println(F("FIFO2 overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus2 & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount2 < packetSize2) fifoCount2 = mpu2.getFIFOCount();

        // read a packet from FIFO
        mpu2.getFIFOBytes(fifoBuffer2, packetSize2);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount2 -= packetSize2;

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu2.dmpGetQuaternion(&q, fifoBuffer2);
            mpu2.dmpGetGravity(&gravity, &q);
            mpu2.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr2\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);
        #endif

    
        #ifdef OUTPUT_TEAPOT
            // display quaternion values in InvenSense Teapot demo format:
            teapotPacket[2] = fifoBuffer[0];
            teapotPacket[3] = fifoBuffer[1];
            teapotPacket[4] = fifoBuffer[4];
            teapotPacket[5] = fifoBuffer[5];
            teapotPacket[6] = fifoBuffer[8];
            teapotPacket[7] = fifoBuffer[9];
            teapotPacket[8] = fifoBuffer[12];
            teapotPacket[9] = fifoBuffer[13];
            Serial.write(teapotPacket, 14);
            teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
        #endif

        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }

//-----------------------------------------------------------------------------------------
//    mpuInterrupt = false;
//    mpuIntStatus = mpu.getIntStatus();
//
//    // get current FIFO count
//    fifoCount = mpu.getFIFOCount();
//    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
//        // reset so we can continue cleanly
//        mpu.resetFIFO();
//        Serial.println(F("FIFO overflow!"));
//
//    // otherwise, check for DMP data ready interrupt (this should happen frequently)
//    } else if (mpuIntStatus & 0x02) {
//        // wait for correct available data length, should be a VERY short wait
//        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
//
//        // read a packet from FIFO
//        mpu.getFIFOBytes(fifoBuffer, packetSize);
//        
//        // track FIFO count here in case there is > 1 packet available
//        // (this lets us immediately read more without waiting for an interrupt)
//        fifoCount -= packetSize;
//
//        #ifdef OUTPUT_READABLE_YAWPITCHROLL
//            // display Euler angles in degrees
//            mpu.dmpGetQuaternion(&q, fifoBuffer);
//            mpu.dmpGetGravity(&gravity, &q);
//            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
//            Serial.print("ypr\t");
//            Serial.print(ypr[0] * 180/M_PI);
//            Serial.print("\t");
//            Serial.print(ypr[1] * 180/M_PI);
//            Serial.print("\t");
//            Serial.println(ypr[2] * 180/M_PI);
//        #endif
//
//    
//        #ifdef OUTPUT_TEAPOT
//            // display quaternion values in InvenSense Teapot demo format:
//            teapotPacket[2] = fifoBuffer[0];
//            teapotPacket[3] = fifoBuffer[1];
//            teapotPacket[4] = fifoBuffer[4];
//            teapotPacket[5] = fifoBuffer[5];
//            teapotPacket[6] = fifoBuffer[8];
//            teapotPacket[7] = fifoBuffer[9];
//            teapotPacket[8] = fifoBuffer[12];
//            teapotPacket[9] = fifoBuffer[13];
//            Serial.write(teapotPacket, 14);
//            teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
//        #endif
//
//        // blink LED to indicate activity
//        blinkState = !blinkState;
//        digitalWrite(LED_PIN, blinkState);
//    }
    //-----------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------
}
