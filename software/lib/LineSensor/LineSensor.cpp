#include "LineSensor.h"
#include <Arduino.h>

LineSensor::LineSensor(int startPin, int numSensors, const int* thresholds) {
    this->startPin = startPin;
    this->numSensors = numSensors;
    this->thresholds = thresholds;
    this->mode = true;
    for (int i = 0; i < numSensors; i++) {
        pinMode(startPin + i, INPUT);
    }
}

int LineSensor::readAngle() {
    if (!mode) {
        return 0;
    }
    float sumX = 0;
    float sumY = 0;
    for (int i = 0; i < numSensors; i++) {
        int readValue = analogRead(startPin + i);
        if (readValue > thresholds[i]) {
            float angle = i * (360.0 / numSensors) * PI / 180.0;
            sumX += cos(angle);
            sumY += sin(angle);
        }
    }
    if (sumX == 0 && sumY == 0) {
        return -1;
    }
    float angle = atan2(sumY, sumX);
    angle = angle * 180 / PI;
    return angle;
}

bool LineSensor::checkOnLine() {
    if (!mode) {
        return false;
    }
    for (int i = 0; i < numSensors; i++) {
        if (analogRead(startPin + i) > thresholds[i]) {
            return true;
        }
    }
    return false;
}

void LineSensor::setMode(bool mode) {
    this->mode = mode;
}