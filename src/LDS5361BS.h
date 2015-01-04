#ifndef LDS5361BS_H
#define LDS5361BS_H

#include <avr/io.h>
#include <util/delay.h>

#ifndef DATA_PORT
  #define DATA_PORT PORTD
#endif

#ifndef DATA_PORT_C
  #define DATA_PORT_C DDRD
#endif

#ifndef CONTROL_PORT
  #define CONTROL_PORT PORTB
#endif

#ifndef CONTROL_PORT_C
  #define CONTROL_PORT_C DDRB
#endif

#define NUM_SEGMENTS 3
#define OUT_MASK ((0x01 << NUM_SEGMENTS) - 1)
#define DOT_PATTERN (0x01 << 4)

void LDS5361BS_init(void);
void LDS5361BS_displayLetter(char letter);
void LDS5361BS_displayLetterDot(char letter);
void LDS5361BS_switchSegment(uint8_t nth);
void LDS5361BS_displayDot(char *string, uint8_t dotPosition);
void LDS5361BS_display(char *string);

#endif
