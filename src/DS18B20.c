#include "DS18B20.h"

void DS18B20_init(void) {
    TEMP_PORT_C |= TEMP_BIT;
    TEMP_PORT |= TEMP_BIT;
}

uint8_t DS18B20_reset(void) {
    uint8_t ok = 0;

    TEMP_PORT &= ~TEMP_BIT;
    TEMP_PORT_C |= TEMP_BIT;
    _delay_us(330); // NOTE Should be 430 us

    TEMP_PORT_C &= ~TEMP_BIT;
    _delay_us(60);

    ok = TEMP_PORT & TEMP_BIT;
    _delay_us(320); // NOTE Should be 420 us

    return !ok;
}

void DS18B20_writeBit(uint8_t bit) {
    TEMP_PORT &= ~TEMP_BIT;
    TEMP_PORT_C |= TEMP_BIT;
    _delay_us(1);

    if(bit) TEMP_PORT_C &= ~TEMP_BIT;

    _delay_us(50);

    TEMP_PORT_C &= ~TEMP_BIT;
}

uint8_t DS18B20_readBit(void) {
    uint8_t bit = 0;

    TEMP_PORT &= ~TEMP_BIT;
    TEMP_PORT_C |= TEMP_BIT;
    _delay_us(1);

    TEMP_PORT_C &= ~TEMP_BIT;
    _delay_us(10);

    if(TEMP_PIN & TEMP_BIT) bit = 1;
    _delay_us(40);

    return bit;
}

void DS18B20_writeByte(uint8_t byte) {
    uint8_t i = 8;

    while(i--) {
        DS18B20_writeBit(byte & 0x1);
        byte >>= 1;
    }
}

uint8_t DS18B20_readByte(void) {
    uint8_t i = 8, byte = 0;

    while(i--) {
        byte >>= 1;
        byte |= DS18B20_readBit() << 7;
    }

    return byte;
}

void DS18B20_convert(void) {
    DS18B20_reset();
    DS18B20_writeByte(0xCC);
    DS18B20_writeByte(0x44);
}

uint8_t DS18B20_isReady(void) {
    return DS18B20_readBit();
}

uint16_t DS18B20_readTemp(void) {
    uint16_t t = 0;
    DS18B20_reset();
    DS18B20_writeByte(0xCC);
    DS18B20_writeByte(0xBE);

    t |= DS18B20_readByte();
    t |= DS18B20_readByte() << 8;
    DS18B20_reset();

    return t;
}

uint16_t DS18B20_getTemp(void) {
    DS18B20_convert();

    while(!DS18B20_isReady());

    return DS18B20_readTemp();
}
