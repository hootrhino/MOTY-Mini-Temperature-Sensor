// Copyright (C) 2024 wwhai
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <Wire.h>
#include "MOTYMini.h"

#define MOTYMiniTempSensor_RESET 0x1E
#define MOTYMiniTempSensor_ADC_READ 0x00
#define MOTYMiniTempSensor_ADC_TEMP_CONV 0x48
#define MOTYMiniTempSensor_PROM_READ 0XA0

MOTYMiniTempSensor::MOTYMiniTempSensor() {
}

void MOTYMiniTempSensor::Init(int addr) {
  addr = addr;
  Wire.beginTransmission(addr);
  Wire.write(MOTYMiniTempSensor_RESET);
  Wire.endTransmission();

  delay(10);

  for (uint8_t i = 0; i < 8; i++) {
    Wire.beginTransmission(addr);
    Wire.write(MOTYMiniTempSensor_PROM_READ + i * 2);
    Wire.endTransmission();

    Wire.requestFrom(addr, 2);
    C[i] = (Wire.read() << 8) | Wire.read();
  }
}

void MOTYMiniTempSensor::read() {

  Wire.beginTransmission(addr);
  Wire.write(MOTYMiniTempSensor_ADC_TEMP_CONV);
  Wire.endTransmission();

  delay(10);

  Wire.beginTransmission(addr);
  Wire.write(MOTYMiniTempSensor_ADC_READ);
  Wire.endTransmission();

  Wire.requestFrom(addr, 3);
  D1 = 0;
  D1 = Wire.read();
  D1 = (D1 << 8) | Wire.read();
  D1 = (D1 << 8) | Wire.read();

  calculate();
}

void MOTYMiniTempSensor::calculate() {
  adc = (double)D1 / 256.0;

  tempValue = (-2) * double(C[1]) / 1000000000000000000000.0f * pow(adc, 4) 
  + 4 * double(C[2]) / 10000000000000000.0f * pow(adc, 3) 
  + (-2) * double(C[3]) / 100000000000.0f * pow(adc, 2) 
  + 1 * double(C[4]) / 1000000.0f * adc 
  + (-1.5) * double(C[5]) / 100.0;
}

double MOTYMiniTempSensor::Temperature() {
  read();
  return tempValue;
}
