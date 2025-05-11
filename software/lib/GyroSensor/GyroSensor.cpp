#include "GyroSensor.h"
#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <Wire.h>

GyroSensor::GyroSensor() {
    this->bno = Adafruit_BNO055(-1, 0x28, &Wire);
    if (!bno.begin()) {
        Serial.println("Failed to initialize BNO055");
    }
    bno.setExtCrystalUse(true);
}

int GyroSensor::readYawAngle() {
    if (!mode) {
        return 0;
    }
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    return euler.z();
}

void GyroSensor::setMode(bool mode) {
    this->mode = mode;
}