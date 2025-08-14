#include<stdint.h>
#include "stdio.h"

class Window {
	uint16_t x, y, w, h;
	public:
		Window(uint16_t winX = 70, uint16_t winY = 50; uint16_t winW = 250; uint16_t winH = 150) {
			x = winX;
			y = winY;
			w = winW;
			h = winH;
			draw_rect(x, y, w+x, h+x, 7);
			draw_rect(x, y, w, y+20, 8);
			draw_rect(w-25, h-15, w-10, h, 4);
		}
		void setPixel(uint16_t X, uint16_t Y, uint8_t color) {
			if(X <= (x+w) && X >= x && Y <= (y+h) && Y >= y) {
				set_pixel(X, Y, color);
			}
		}
		uint8_t getPixel(uint16_t X, uint16_t Y) {
			if(X <= (x+w) && X >= x && Y <= (y+h) && Y >= y) {
				return get_pixel(X, Y);
			}
		}
		void close() {
			draw_rect(x, y, w+x, h+y, 0);
		}
		~Window() {
			close();
		}
};
