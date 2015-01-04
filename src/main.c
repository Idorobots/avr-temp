#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#define DATA_PORT PORTD
#define DATA_PORT_C DDRD
#define CONTROL_PORT PORTB
#define CONTROL_PORT_C DDRB
#include "LDS5361BS.h"

#define TEMP_PORT PORTC
#define TEMP_PORT_C DDRC
#define TEMP_PIN PINC
#define TEMP_BIT 0x1
#include "DS18B20.h"


int formatNum(char *str, int num) {
    uint8_t i = 0;
    uint8_t dotPos = NUM_SEGMENTS;

    if(num < 0) {
        str[i++] = '-';
        num = -num;
    }

    int high = num >> 0x4;
    int low = (num & 0xF) * 625;

    if(high >= 100) {
        str[i++] = (high / 100) + '0';
        high = high % 100;
    }

    if(high >= 10) {
        str[i++] = (high / 10) + '0';
    }

    str[i++] = (high % 10) + '0';

    dotPos = i - 1;

    str[i++] = (low / 1000) + '0';
    low = low % 1000;

    str[i++] = (low / 100) + '0';
    low = low % 100;

    return dotPos;
}

int main (void) {
    DS18B20_init();
    LDS5361BS_init();

    _delay_ms(10);

    char num[10];
    int currTemp = 0;
    int dotPos = formatNum(num, currTemp);

    wdt_enable(WDTO_2S);

    while (1) {
        wdt_reset();

        LDS5361BS_displayDot(num, dotPos);
        DS18B20_convert();

        while(!DS18B20_isReady()) {
            LDS5361BS_displayDot(num, dotPos);
            _delay_ms(1);
        }

        LDS5361BS_displayDot(num, dotPos);
        currTemp = DS18B20_readTemp();
        dotPos = formatNum(num, currTemp);
    }

    return 1;
}
