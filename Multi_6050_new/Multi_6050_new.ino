
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu(0x68), mpu1(0x68), mpu2(0x68), mpu3(0x68);
//MPU6050 mpu(0x69); // <-- use for AD0 high


// uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
// pitch/roll angles (in degrees) calculated from the quaternions coming
// from the FIFO. Note this also requires gravity vector calculations.
// Also note that yaw/pitch/roll angles suffer from gimbal lock (for
// more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)
#define OUTPUT_READABLE_YAWPITCHROLL


//#define INTERRUPT_PIN 4  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 16 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;
//-----------------------------------------------------------------------------------
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
//-----------------------------------------------------------------------------------
// MPU1 control/status vars
bool dmpReady1 = false;  // set true if DMP init was successful
uint8_t mpuIntStatus1;   // holds actual interrupt status byte from MPU
uint8_t devStatus1;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize1;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount1;     // count of all bytes currently in FIFO
uint8_t fifoBuffer1[64]; // FIFO storage buffer
//-----------------------------------------------------------------------------------
// MPU2 control/status vars
bool dmpReady2 = false;  // set true if DMP init was successful
uint8_t mpuIntStatus2;   // holds actual interrupt status byte from MPU
uint8_t devStatus2;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize2;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount2;     // count of all bytes currently in FIFO
uint8_t fifoBuffer2[64]; // FIFO storage buffer
//-----------------------------------------------------------------------------------
// MPU control/status vars
bool dmpReady3 = false;  // set true if DMP init was successful
uint8_t mpuIntStatus3;   // holds actual interrupt status byte from MPU
uint8_t devStatus3;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize3;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount3;     // count of all bytes currently in FIFO
uint8_t fifoBuffer3[64]; // FIFO storage buffer
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
//uint8_t teapotPacket[14] = { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };


// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin(0, 2);
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize serial communication
  // (115200 chosen because it is required for Teapot Demo output, but it's
  // really up to you depending on your project)
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately

  // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3v or Ardunio
  // Pro Mini running at 3.3v, cannot handle this baud rate reliably due to
  // the baud timing being too misaligned with processor ticks. You must use
  // 38400 or slower in these cases, or use some kind of external separate
  // crystal solution for the UART timer.

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  //-----------------------------------------------------------------------------------
  boot(12);
  delay(10);
  mpu.initialize();
  Serial.println(F("Testing device0 connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection -------successful") : F("MPU6050 connection ---------failed"));
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788);
  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
  //-----------------------------------------------------------------------------------
  boot(14);
  delay(10);
  mpu1.initialize();
  //pinMode(INTERRUPT_PIN, INPUT);

  // verify connection
  Serial.println(F("Testing device1 connections..."));
  Serial.println(mpu1.testConnection() ? F("MPU6050 connection -------successful") : F("MPU6050 connection -------failed"));
  Serial.println(F("Initializing DMP..."));
  devStatus1 = mpu1.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu1.setXGyroOffset(220);
  mpu1.setYGyroOffset(76);
  mpu1.setZGyroOffset(-85);
  mpu1.setZAccelOffset(1788); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  if (devStatus1 == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu1.setDMPEnabled(true);
    mpuIntStatus1 = mpu1.getIntStatus();
    dmpReady1 = true;

    // get expected DMP packet size for later comparison
    packetSize1 = mpu1.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus1);
    Serial.println(F(")"));
  }
  //-----------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------
  boot(13);
  delay(10);
  mpu2.initialize();
  Serial.println(F("Testing device0 connections..."));
  Serial.println(mpu2.testConnection() ? F("MPU6050 connection -------successful") : F("MPU6050 connection ---------failed"));
  Serial.println(F("Initializing DMP..."));
  devStatus2 = mpu2.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu2.setXGyroOffset(220);
  mpu2.setYGyroOffset(76);
  mpu2.setZGyroOffset(-85);
  mpu2.setZAccelOffset(1788); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  if (devStatus2 == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu2.setDMPEnabled(true);
    mpuIntStatus2 = mpu2.getIntStatus();
    dmpReady2 = true;
    packetSize2 = mpu2.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus2);
    Serial.println(F(")"));
  }
  //-----------------------------------------------------------------------------------
  boot(15);
  delay(10);
  mpu3.initialize();
  Serial.println(F("Testing device3 connections..."));
  Serial.println(mpu3.testConnection() ? F("MPU6050 connection -------successful") : F("MPU6050 connection ---------failed"));
  Serial.println(F("Initializing DMP..."));
  devStatus3 = mpu3.dmpInitialize();
  mpu3.setXGyroOffset(220);
  mpu3.setYGyroOffset(76);
  mpu3.setZGyroOffset(-85);
  mpu3.setZAccelOffset(1788);
  // make sure it worked (returns 0 if so)
  if (devStatus3 == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu3.setDMPEnabled(true);
    mpuIntStatus3 = mpu3.getIntStatus();
    dmpReady3 = true;
    packetSize3 = mpu3.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus3);
    Serial.println(F(")"));
  }
  //-----------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------
  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
  Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================
void boot(int pin) {
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
    digitalWrite(pin, LOW);
//  digitalWrite(12, LOW);
//  digitalWrite(13, LOW);
//  digitalWrite(14, LOW);
//  digitalWrite(15, LOW);
//  digitalWrite(pin, HIGH);
}

int iCount = 0;
void loop() {

  bool ic0 = 0, ic1 = 0, ic2 = 0, ic3 = 0, ic4 = 0;
  // if programming failed, don't try to do anything
  if (!dmpReady) return;
  else if (!dmpReady1) return;
  else if (!dmpReady2) return;
  //--------------------------------boot(12);---------------------------------------------------
  boot(12);
  // reset interrupt flag and get INT_STATUS byte
  //mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    //Serial.println(F("FIFO0 overflow!"));
    Serial.print("ypr0\tFIFO\tover\tflow");
    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait

    ic0 = 1;
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
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[2] * 180 / M_PI);
#endif
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);

  } else Serial.print("ypr0\t    \t    \t    ");
  //--------------------------------boot(13);---------------------------------------------------
  boot(13);
  // reset interrupt flag and get INT_STATUS byte
  //mpuInterrupt = false;
  mpuIntStatus2 = mpu2.getIntStatus();

  // get current FIFO count
  fifoCount2 = mpu2.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus2 & 0x10) || fifoCount2 == 1024) {
    // reset so we can continue cleanly
    mpu2.resetFIFO();
    //Serial.println(F("FIFO0 overflow!"));
    Serial.print("\typr2\tFIFO\tover\tflow");
    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus2 & 0x02) {
    // wait for correct available data length, should be a VERY short wait

    ic2 = 1;
    while (fifoCount2 < packetSize2) fifoCount2 = mpu2.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer2, packetSize2);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount2 -= packetSize2;

#ifdef OUTPUT_READABLE_YAWPITCHROLL
    // display Euler angles in degrees
    mpu2.dmpGetQuaternion(&q, fifoBuffer2);
    mpu2.dmpGetGravity(&gravity, &q);
    mpu2.dmpGetYawPitchRoll(ypr, &q, &gravity);
    Serial.print("\typr2\t");
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[2] * 180 / M_PI);
#endif
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);

  } else Serial.print("\typr2\t    \t    \t    ");
  //--------------------------------boot(15);---------------------------------------------------
  boot(15);
  // reset interrupt flag and get INT_STATUS byte
  //mpuInterrupt = false;
  mpuIntStatus3 = mpu3.getIntStatus();

  // get current FIFO count
  fifoCount3 = mpu3.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus3 & 0x10) || fifoCount3 == 1024) {
    // reset so we can continue cleanly
    mpu3.resetFIFO();
    //Serial.println(F("FIFO0 overflow!"));
    Serial.print("\typr3\tFIFO\tover\tflow");
    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus3 & 0x02) {
    // wait for correct available data length, should be a VERY short wait

    ic3 = 1;
    while (fifoCount3 < packetSize3) fifoCount3 = mpu3.getFIFOCount();

    // read a packet from FIFO
    mpu3.getFIFOBytes(fifoBuffer3, packetSize3);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount3 -= packetSize3;

#ifdef OUTPUT_READABLE_YAWPITCHROLL
    // display Euler angles in degrees
    mpu3.dmpGetQuaternion(&q, fifoBuffer3);
    mpu3.dmpGetGravity(&gravity, &q);
    mpu3.dmpGetYawPitchRoll(ypr, &q, &gravity);
    Serial.print("\typr3\t");
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[2] * 180 / M_PI);
#endif
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);

  } else Serial.print("\typr3\t    \t    \t    ");

  //--------------------------------------boot(14);---------------------------------------------
  boot(14);
  // reset interrupt flag and get INT_STATUS byte
  //mpuInterrupt = false;
  mpuIntStatus1 = mpu1.getIntStatus();

  // get current FIFO count
  fifoCount1 = mpu1.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus1 & 0x10) || fifoCount1 == 1024) {
    // reset so we can continue cleanly
    mpu1.resetFIFO();
    //Serial.println(F("FIFO1 overflow!"));
    Serial.print("ypr1\tFIFo\tover\tflow");
    Serial.print("\t");
    iCount += 1;
    Serial.println(iCount);
    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus1 & 0x02) {

    ic1 = 1;
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
    Serial.print("\typr1\t");
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[2] * 180 / M_PI);
#endif
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
    iCount += 1;
    Serial.print("\t");
    Serial.println(iCount);

    //    if (ic0 == 1 && ic1 == 1) {
    //      Serial.print("\tBOTH");
    //    }
    //    else if (ic0 == 1) {
    //      Serial.print("\tic 0");
    //    }
    //    else if (ic1 == 1) {
    //      Serial.print("\tic 1");
    //    }
    //    else Serial.print("\tNO one");
    //    Serial.print("\t");
    //    iCount += 1;
    //    Serial.println(iCount);
  } else {
    Serial.print("\typr1\t    \t    \t    \t");
    iCount += 1;
    Serial.println(iCount);
  }

//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
}
