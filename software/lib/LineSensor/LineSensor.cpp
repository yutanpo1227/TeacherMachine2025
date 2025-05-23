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
    float sumX = 0;
    float sumY = 0;
    for (int i = 0; i < numSensors; i++) {
        int readValue = analogRead(startPin + i);
        if (readValue < thresholds[i]) {
            sumX += cos(i * 2 * PI / numSensors);
            sumY += sin(i * 2 * PI / numSensors);
        }
    }
    float angle = atan2(sumY, sumX);
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