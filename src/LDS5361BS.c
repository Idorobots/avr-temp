#include "LDS5361BS.h"

static char ascii[128] = {
    // Whitespace
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // Punctuation
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    // Digits & more punctuation
    0xEE, 0x60, 0xCD, 0xE9, 0x63, 0xAB, 0xAF, 0xE0, 0xEF, 0xEB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // Uppercase letters & punctuation
    0x00, 0xE7, 0x2F, 0x0D, 0x6D, 0x8F, 0x87, 0xE3, 0x67, 0x60, 0x68, 0x67, 0x0E, 0x25, 0x25, 0x2D,
    0xC7, 0xEE, 0x05, 0xAB, 0x0F, 0x6E, 0x6E, 0x6E, 0x67, 0x63, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x08,
    // Lowercase letters & punctuation
    0x00, 0xE7, 0x2F, 0x0D, 0x6D, 0x8F, 0x87, 0xE3, 0x67, 0x60, 0x68, 0x67, 0x0E, 0x25, 0x25, 0x2D,
    0xC7, 0xEE, 0x05, 0xAB, 0x0F, 0x6E, 0x6E, 0x6E, 0x67, 0x63, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x00
};

void LDS5361BS_init(void) {
    DATA_PORT = 0x00;
    DATA_PORT_C = 0xff;

    CONTROL_PORT &= ~OUT_MASK;
    CONTROL_PORT_C |= OUT_MASK;
}

void LDS5361BS_displayLetter(char letter) {
    DATA_PORT = ~letter;
}

void LDS5361BS_displayLetterDot(char letter) {
    LDS5361BS_displayLetter(letter | DOT_PATTERN);
}

void LDS5361BS_switchSegment(uint8_t nth) {
    DATA_PORT = 0xFF;
    CONTROL_PORT &= ~OUT_MASK;
    CONTROL_PORT |= 0x01 << nth;
    _delay_us(10);
}

void LDS5361BS_displayDot(char *string, uint8_t dotPosition) {
    uint8_t i = 0;

    for(i = 0; i < NUM_SEGMENTS; ++i) {
        LDS5361BS_switchSegment(i);

        if(i == dotPosition) {
            LDS5361BS_displayLetterDot(ascii[(uint8_t) string[i]]);
        } else {
            LDS5361BS_displayLetter(ascii[(uint8_t) string[i]]);
        }

        if(i < NUM_SEGMENTS - 1) _delay_ms(1);
        // NOTE Last segment is left without a delay to make time for other code.
    }
}

void LDS5361BS_display(char *string) {
    LDS5361BS_displayDot(string, NUM_SEGMENTS);
}