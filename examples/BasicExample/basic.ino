
#include <Wire.h>
#include "MOTYMini.h"

MOTYMiniTempSensor sensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensor.Init(0x77);
}

void loop() {
  Serial.println(sensor.Temperature(), 4);
  delay(10);
}
