#include <Arduino.h>
#include "LineSensor.h"
#include "IRSensor.h"

int thresholds[] = {200, 200, 200, 200, 200, 200, 200, 200};
LineSensor lineSensor(0, 8, thresholds);
IRSensor irSensor(22, 8);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(lineSensor.readAngle());
  Serial.println(irSensor.readAngle());
}