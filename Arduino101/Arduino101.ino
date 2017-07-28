#include <CurieIMU.h>
#include <CurieBLE.h>

#define buttonPin 4

unsigned long microsPerReading, microsPrevious;
float accelScale;
float vx, vy, vz, vh, vv;

BLEService orientationService("19B10010-E8F2-537E-4F6C-D104768A1214"); // create service
BLECharacteristic orientationCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 20); // allows remote device to get notifications

void setup() {
  Serial.begin(9600);

  // start the IMU and filter
  CurieIMU.begin();
  CurieIMU.setAccelerometerRate(25);

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);

  // initialize variables to pace updates to correct rate
  microsPerReading = 1000000 / 25;
  microsPrevious = micros();

  // begin initialization
  BLE.begin();

  // set the local name peripheral advertises
  BLE.setLocalName("Orientation");
  // set the UUID for the service this peripheral advertises:
  BLE.setAdvertisedService(orientationService);

  // add the characteristics to the service
  orientationService.addCharacteristic(orientationCharacteristic);

  // add the service
  BLE.addService(orientationService);

  orientationCharacteristic.setValue("Loading...");

  // start advertising
  BLE.advertise();

  // Set initial velocity
  vx = 0;
  vy = 0;
  vz = 0;
  vv = 0;
  vh = 0;
}

void loop() {
  int aix, aiy, aiz;
  float ax, ay, az;
  unsigned long microsNow;

  // check if it's time to read data and update the filter
  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) {
    // read raw data from CurieIMU
    CurieIMU.readAccelerometer(aix, aiy, aiz);

    // convert from raw data to m/s^2
    ax = convertRawAcceleration(aix);
    ay = convertRawAcceleration(aiy);
    az = convertRawAcceleration(aiz);

    // time = 25 us, because we set that above
    vx = vx + ax * 25E-6;
    vy = vy + ay * 25E-6;
    vz = vz + az * 25E-6;

    vh = sqrt(pow(vx, 2) + pow(vy, 2));
    vv = vz;

    // Package and send over BLE and locally over serial
    String stringOutput = "[" + String(vv, 3) + "," + String(vz, 3) + "]";
    orientationCharacteristic.setValue(stringOutput.c_str());
    Serial.println(stringOutput);

    // increment previous time, so we keep proper pace
    microsPrevious = microsPrevious + microsPerReading;
  }

  // Check button
  if(digitalRead(buttonPin)) {
    // Keep reseting to 0 until you lift your finger off of the button
    vx = 0;
    vy = 0;
    vz = 0;
    vv = 0;
    vh = 0;
  }
  
}

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  float a = 9.8 * (aRaw * 2.0) / 32768.0;
  return a;
}
