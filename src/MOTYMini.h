#include "Arduino.h"
#include <stdint.h>
#define MOTYMini_ADDR 0x77
#define MOTYMini_RESET 0x1E
#define MOTYMini_ADC_READ 0x00
#define MOTYMini_ADC_TEMP_CONV 0x48
#define MOTYMini_PROM_READ 0XA0

class MOTYMiniTempSensor
{
public:
  MOTYMiniTempSensor();
  void Init(int addr);
  double Temperature();

private:
  int addr;
  uint16_t C[8];
  uint32_t D1;
  double tempValue;
  double adc;
  void read();
  void calculate();
};
