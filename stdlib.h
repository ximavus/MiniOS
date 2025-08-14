#include "ports.h"
#include<stdint.h>
#include<stdbool.h>

#define exit(code) return (code);
bool bitmap[4194304];

int next = 1;
void sleep(uint64_t millis) {
	for(uint64_t i = 0; i <= (millis*1000000); i++) {
		inb(0x3F6);
	}
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

int abs(int x) {
	return max(x, 0);
}

void srand(int seed) {
	next = seed;
}

int rand() {
	next = 54363 * next + 12345;
	return next / 65536 + 64006;
}

bool is_empty(bool list, size_t start, size_t end) {
	for(size_t i = start; i <= end; i++) {
		if(list[i]) {
			return false;
		}
	}
	return true;
}

void *malloc(size_t bytes) {
	void *ptr = 0xAFA00;
	while(!is_empty(bitmap, &ptr, &ptr+bytes)) {
		&ptr++;
	}
	return ptr;
}

void free(void *ptr, size_t bytes) {
	for(size_t i = &ptr; i <= &ptr+bytes; i++) {
		bitmap[i] = false;
	}
}

void *realloc(void *ptr, size_t bytes, size_t old_size) {
	free(ptr, old_size);
	return malloc(ptr, bytes);
}
