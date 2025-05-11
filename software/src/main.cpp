#include <Arduino.h>
#include <Wire.h>
#include "LineSensor.h"
#include "IRSensor.h"
#include "MotorController.h"
#include "Motor.h"
#include "GyroSensor.h"

#define ENABLE_LINE_SENSOR false
#define ENABLE_GYRO_SENSOR false

#define SPEED 127
#define GYRO_THRESHOLD 30

const int lineThresholds[] = {200, 200, 200, 200, 200, 200, 200, 200};

LineSensor lineSensor = LineSensor(0, 8, lineThresholds);
IRSensor irSensor = IRSensor(22, 8);
GyroSensor gyroSensor = GyroSensor();

Motor motor1 = Motor(2, 3);
Motor motor2 = Motor(5, 6);
Motor motor3 = Motor(7, 8);
Motor motor4 = Motor(11, 12);
MotorController motorController = MotorController(&motor1, &motor2, &motor3, &motor4);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  // 各センサーを有効にするかどうか
  lineSensor.setMode(ENABLE_LINE_SENSOR);
  gyroSensor.setMode(ENABLE_GYRO_SENSOR);
}

void loop() {
  // ライン上にいるなら、ラインの角度の反対に進む
  if (lineSensor.checkOnLine()) {
    int moveAngle = lineSensor.readAngle() - 180;
    motorController.moveDirection(moveAngle, SPEED);
    return;
  }

  const int gyroAngle = gyroSensor.readYawAngle();
  // ジャイロセンサーが閾値以上であれば姿勢を修正する
  if (gyroAngle > 0 && gyroAngle > GYRO_THRESHOLD) {
    motorController.turnRight(abs(gyroAngle));
    return;
  } else if (gyroAngle < 0 && gyroAngle > -GYRO_THRESHOLD) {
    motorController.turnLeft(abs(gyroAngle));
    return;
  }

  const int ballAngle = irSensor.readAngle();
  const int ballDist = irSensor.readDistance();
  // ボールが近い時は大きく回り込む
  if (ballDist > 100) {
    motorController.moveDirection(ballAngle * 1.5, SPEED);
  } else {
    motorController.moveDirection(ballAngle, SPEED);
  }
}