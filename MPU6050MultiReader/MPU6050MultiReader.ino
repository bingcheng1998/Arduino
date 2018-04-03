#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// ================================================================
// ===                   You can change here                    ===
// ================================================================

#define TIME_COUNTER //Count the times of reading from all the mpu6050s
#define SerialPort 115200
#define mpuNum 4
static int bootPin[mpuNum] = {12, 13, 14, 15};
static int XGyroOffset[mpuNum] = {113, 46, 53, 102};
static int YGyroOffset[mpuNum] = {-11, 14, 1, -12};
static int ZGyroOffset[mpuNum] = {-35, -41, -129, 15};
static int ZAccelOffset[mpuNum] = {1677, 926, 924, 745};

// ================================================================
// ===                   Do NOT change below                    ===
// ================================================================

// AD0 low = 0x68
// AD0 high = 0x69
MPU6050 mpu[mpuNum];
#define OUTPUT_READABLE_YAWPITCHROLL
#define LED_PIN 16
bool blinkState = false;

// MPU control/status vars
bool dmpReady[mpuNum];  // set true if DMP init was successful
uint8_t mpuIntStatus[mpuNum];   // holds actual interrupt status byte from MPU
uint8_t devStatus[mpuNum];      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize[mpuNum];    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount[mpuNum];     // count of all bytes currently in FIFO
uint8_t fifoBuffer[mpuNum][64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// ================================================================
// ===                      BOOT                                ===
// ================================================================

void boot(int pin) {
  for (int i = 0; i < mpuNum; ++i)
  {
    digitalWrite(bootPin[i], HIGH);
  }
  digitalWrite(pin, LOW);
}

#ifdef TIME_COUNTER
int iCount = 0;
#endif

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

  for (int i = 0; i < mpuNum; ++i)
  {
    pinMode(bootPin[i], OUTPUT);
  }

  Serial.begin(SerialPort);
  while (!Serial);

  for (int i = 0; i < mpuNum; i++) {
    boot(bootPin[i]);
    // initialize device
    Serial.print(F("Initializing MPU6050 ic = "));
    Serial.println(i);
    mpu[i].initialize();

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu[i].testConnection() ? F("MPU6050 connection --------successful") : F("MPU6050 connection --------failed"));
    Serial.println(F("Initializing DMP..."));
    devStatus[i] = mpu[i].dmpInitialize();

    mpu[i].setXGyroOffset(XGyroOffset[i]);
    mpu[i].setYGyroOffset(YGyroOffset[i]);
    mpu[i].setZGyroOffset(ZGyroOffset[i]);
    mpu[i].setZAccelOffset(ZAccelOffset[i]);
    if (devStatus[i] == 0) {
      // turn on the DMP, now that it's ready
      Serial.println(F("Enabling DMP..."));
      mpu[i].setDMPEnabled(true);
      mpuIntStatus[i] = mpu[i].getIntStatus();
      dmpReady[i] = true;
      packetSize[i] = mpu[i].dmpGetFIFOPacketSize();
    } else {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      Serial.print(F("DMP Initialization failed (code "));
      Serial.print(devStatus[i]);
      Serial.println(F(")"));
    }
  }

  Serial.println(F("\nSend any character to begin DMP: "));
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again
  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {

  for (int i = 0; i < mpuNum; ++i)
  {
    if (!dmpReady[i]) return;
    // if programming failed, don't try to do anything
  }


  for (int i = 0; i < mpuNum; ++i)
  {
    boot(bootPin[i]);
    // reset interrupt flag and get INT_STATUS byte
    //mpuInterrupt = false;
    mpuIntStatus[i] = mpu[i].getIntStatus();

    // get current FIFO count
    fifoCount[i] = mpu[i].getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus[i] & 0x10) || fifoCount[i] == 1024) {
      // reset so we can continue cleanly
      mpu[i].resetFIFO();
      //Serial.println(F("FIFO0 overflow!"));
      Serial.print("ypr");
      Serial.print(i);
      Serial.print("\tFIFO\tover\tflow");
      // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus[i] & 0x02) {
      // wait for correct available data length, should be a VERY short wait

      while (fifoCount[i] < packetSize[i]) fifoCount[i] = mpu[i].getFIFOCount();

      // read a packet from FIFO
      mpu[i].getFIFOBytes(fifoBuffer[i], packetSize[i]);

      // track FIFO count here in case there is > 1 packet available
      // (this lets us immediately read more without waiting for an interrupt)
      fifoCount[i] -= packetSize[i];

#ifdef OUTPUT_READABLE_YAWPITCHROLL
      // display Euler angles in degrees
      mpu[i].dmpGetQuaternion(&q, fifoBuffer[i]);
      mpu[i].dmpGetGravity(&gravity, &q);
      mpu[i].dmpGetYawPitchRoll(ypr, &q, &gravity);
      Serial.print("ypr");
      Serial.print(i);
      Serial.print("\t");
      Serial.print(ypr[0] * 180 / M_PI);
      Serial.print("\t");
      Serial.print(ypr[1] * 180 / M_PI);
      Serial.print("\t");
      Serial.print(ypr[2] * 180 / M_PI);
#endif
      // blink LED to indicate activity
      blinkState = !blinkState;
      digitalWrite(LED_PIN, blinkState);

    } else {
      Serial.print("ypr");
      Serial.print(i);
      Serial.print("\t    \t    \t    ");
    }
    Serial.print("\t");
#ifdef TIME_COUNTER
    iCount ++;
#endif
  }
#ifdef TIME_COUNTER
  Serial.println(iCount);
#endif
#ifndef TIME_COUNTER
  Serial.println();
#endif
}
