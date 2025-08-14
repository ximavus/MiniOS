#include "ports.h"
#include<stdint.h>
#include<stdbool.h>

#define WIDTH 320
#define HEIGHT 200

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
