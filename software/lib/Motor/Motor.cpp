#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int phPin, int enPin) {
    this->phPin = phPin;
    this->enPin = enPin;
}

void Motor::setSpeed(int speed) {
    if (speed > 0) {
        digitalWrite(phPin, HIGH);
    } else {
        digitalWrite(phPin, LOW);
    }
    analogWrite(enPin, abs(speed));
}