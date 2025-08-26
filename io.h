#include<stdint.h>
#include<stdbool.h>

void memset(uint32_t addr, uint8_t val) {
	*(uint8_t*)addr = val;
}
// DELAY FUNCTION
void delay(int timeout) {
	while(timeout--);
}
// PORT IO
void outb(uint16_t port, uint8_t data) {
        asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
        return;
}
uint8_t inb(uint16_t port) {
        uint8_t res;
        asm volatile("inb %1, %0" : "=a"(res) : "Nd"(port));
	return res;
}

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
    22,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    20,	/* Left Arrow */
    0,
    21,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    23,	/* Down Arrow */
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
	return kbdus[(unsigned char) inb(0x60)];
}
bool kbhit() {
	if(getch() != 0) {
		return true;
	}
	return false;
}

// OUTPUT
uint8_t col = 0;
uint8_t row = 0;

#define WIDTH 80
#define HEIGHT 25

void set_cursor_pos(uint8_t x, uint8_t y) {
	if(x <= WIDTH && x >= 0 && y <= HEIGHT && y >= 0) {
		uint16_t pos = y * WIDTH + x;
		outb(0x3D4, 0x0F);
		outb(0x3D5, (uint8_t) (pos & 0xFF));
		outb(0x3D4, 0x0E);
		outb(0x3D5, (uint8_t) ((pos) >> 8) & 0xFF);
	}
}
void set_char(uint8_t x, uint8_t y, char c) {
	if(x <= WIDTH && x >= 0 && y <= HEIGHT && y >= 0) {
		*(char *)(0xb8000+(2*(WIDTH*y+x))-2) = c;
	}
}
bool is_print(char c) {
	if(c > 31 && c < 127) {
		return true;
	}
	return false;
}
void putchar(char c) {
	if(is_print(c)) {
		if(col++ > WIDTH) {
			col = 0;
			row++;
		}
		set_char(col, row, c);
	}
	else {
		switch(c) {
			case '\n':
				col = 0;
				if(row < WIDTH) {
					row++;
				}
			case '\b':
				if(col > 0) {
					col--;
				}
				if(row > 0) {
					row--;
				}
				set_char(col+1, row, ' ');
			case 20:
				if(col > 0) {
					col--;
					set_cursor_pos(col, row);
				}
			case 21:
				if(col < WIDTH) {
					col++;
					set_cursor_pos(col, row);
				}
			case 22:
				if(row > 0) {
					row--;
					set_cursor_pos(col, row);
				}
			case 23:
				if(row < HEIGHT) {
					row++;
					set_cursor_pos(col, row);
				}
			default:
				break;
		}
	}
	set_cursor_pos(col, row);
}
void print(const char *str) {
	for(int i = 0; str[i]; i++) {
		putchar(str[i]);
	}
}
