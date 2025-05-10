#include "IRSensor.h"
#include <Arduino.h>

IRSensor::IRSensor(int startPin, int numSensors) {
    this->startPin = startPin;
    this->numSensors = numSensors;
    for (int i = 0; i < numSensors; i++) {
        pinMode(startPin + i, INPUT);
    }
}

int IRSensor::readAngle() {
    float sumX = 0;
    float sumY = 0;
    for (int i = 0; i < numSensors; i++) {
        int readValue = pulseIn(startPin + i, LOW);
        sumX += cos(readValue * 2 * PI / numSensors);
        sumY += sin(readValue * 2 * PI / numSensors);
    }
    float angle = atan2(sumY, sumX);
    return angle;
}

int IRSensor::readDistance() {
    float sumX = 0;
    float sumY = 0;
    for (int i = 0; i < numSensors; i++) {
        int readValue = pulseIn(startPin + i, LOW);
        sumX += cos(readValue * 2 * PI / numSensors);
        sumY += sin(readValue * 2 * PI / numSensors);
    }
    float distance = sqrt(sumX * sumX + sumY * sumY);
    return distance;
}