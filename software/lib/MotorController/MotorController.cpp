#include "MotorController.h"
#include "Motor.h"

MotorController::MotorController(Motor* motor1, Motor* motor2, Motor* motor3, Motor* motor4) {
    this->motor1 = motor1;
    this->motor2 = motor2;
    this->motor3 = motor3;
    this->motor4 = motor4;
}

void MotorController::moveDirection(int direction, int speed) {
    float m1SpeedParam = sin(direction-45);
    float m2SpeedParam = sin(direction+45);
    float m3SpeedParam = sin(direction-135);
    float m4SpeedParam = sin(direction+135);

    float speedParams[4] = {m1SpeedParam, m2SpeedParam, m3SpeedParam, m4SpeedParam};
    int maxSpeedParam = 0;

    for (int i = 0; i < 4; i++) {
        if (abs(speedParams[i]) > maxSpeedParam) {
            maxSpeedParam = abs(speedParams[i]);
        }
    }

    float ratio = 1 / maxSpeedParam;

    motor1->setSpeed(speed * speedParams[0] * ratio);
    motor2->setSpeed(speed * speedParams[1] * ratio);
    motor3->setSpeed(speed * speedParams[2] * ratio);
    motor4->setSpeed(speed * speedParams[3] * ratio);
}

void MotorController::turnRight(int speed) {
    motor1->setSpeed(speed);
    motor2->setSpeed(speed);
    motor3->setSpeed(speed);
    motor4->setSpeed(speed);
}

void MotorController::turnLeft(int speed) {
    motor1->setSpeed(-speed);
    motor2->setSpeed(-speed);
    motor3->setSpeed(-speed);
    motor4->setSpeed(-speed);
}

void MotorController::stop() {
    motor1->setSpeed(0);
    motor2->setSpeed(0);
    motor3->setSpeed(0);
    motor4->setSpeed(0);
}