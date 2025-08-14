#include "ports.h"
#include<stdint.h>
#include<stdbool.h>


#define WIDTH 320
#define HEIGHT 200

// INPUT
const char kbdus[128] = {
0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

enum scan_codes
{
    LEFT_ARROW_PRESSED = 0x4b,
    RIGHT_ARROW_PRESSED = 0x4d,
    DOWN_ARROW_PRESSED = 0x50,
    UP_ARROW_PRESSED = 0x48,
    LEFT_SHIFT_PRESSED = 0x2a,
    CAPS_LOCK_PRESSED = 0x3a,
    RETURN_PRESSED = 0x1c,
    F5_PRESSED = 0x3f,
    LEFT_SHIFT_RELEASED = 0xaa,
    CTRL_PRESSED = 0x1d,
    CTRL_RELEASED = 0x9d
};
char getch() {
	unsigned char scancode;
	scancode = inb(0x60);
	return kbdus[scancode];
}
bool kbhit() {
	if(getch() != 0) {
		return true;
	}
	return false;
}
// TODO fix mouse input
/*void mouse_wait(uint8_t type) {
	uint32_t timeout = 100000;
	while(timeout--) {
		if((inb(0x64) & (type == 0x0 ? 0x1 : 0x2)) == 0) return;
	}
	return;
}
uint8_t getclick() {
	mouse_wait(0x0);
	return inb(0x60);
}*/

void set_pixel(uint16_t x, uint16_t y, uint8_t color) {
	*(uint8_t*) (0xA0000+(y*WIDTH+x)) = color;
}

uint8_t get_pixel(uint16_t x, uint16_t y) {
	return *(uint8_t) (0xA0000+(y*WIDTH+x));
}

void draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color) {
	if(x2 < x1) {
		uint16_t tmpx = x1;
		x1 = x2;
		x2 = tmpx;
	}
	if(y2 < y1) {
		uint16_t tmpy = y1;
		y1 = y2;
		y2 = tmpy;
	}
	for(uint16_t x = x1; x <= x2; x++) {
		for(uint16_t y = y1; y <= y2; y++) {
			set_pixel(x, y, color);
		}
	}
}

void clrscr(uint8_t color) {
	draw_rect(0, 0, WIDTH, HEIGHT, color);
}
