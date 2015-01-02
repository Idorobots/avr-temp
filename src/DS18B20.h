#ifndef DS18B20_H
#define DS18B20_H

#include <avr/io.h>
#include <util/delay.h>

#ifndef TEMP_PORT
  #define TEMP_PORT PORTC
#endif

#ifndef TEMP_PORT_C
  #define TEMP_PORT_C DDRC
#endif

#ifndef TEMP_PIN
  #define TEMP_PIN PINC
#endif

#ifndef TEMP_BIT
  #define TEMP_BIT 0x1
#endif

void DS18B20_init(void);
uint8_t DS18B20_reset(void);
void DS18B20_writeBit(uint8_t bit);
uint8_t DS18B20_readBit(void);
void DS18B20_writeByte(uint8_t byte);
uint8_t DS18B20_readByte(void);
void DS18B20_convert(void);
uint8_t DS18B20_isReady(void);
uint16_t DS18B20_readTemp(void);
uint16_t DS18B20_getTemp(void);

#endif
