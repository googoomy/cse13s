#include "code.h"

#include "defines.h"

#include <inttypes.h>
#include <stdio.h>
/*
typedef struct { 
	uint32_t top;
	uint8_t bits[MAX_CODE_SIZE];
} Code;
*/
Code code_init(void) {
    Code c = { .top = 0, .bits = { 0 } };
    return c;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    }
    return false;
}

bool code_set_bit(Code *c, uint32_t i) {
    if (i < ALPHABET) {
        c->bits[i / 8] = 1;
        return true;
    }
    return false;
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (i < ALPHABET) {
        c->bits[i / 8] = 0;
        return true;
    }
    return false;
}

bool code_get_bit(Code *c, uint32_t i) {
    if (i < ALPHABET && c->bits[i / 8] == 1) {
        return true;
    }
    return false;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    c->bits[c->top / 8] = bit;
    c->top += 1;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    *bit = c->bits[c->top / 8];
    c->top -= 1;
    return true;
}

void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i += 1) {
        printf("%" PRIu32, c->bits[i]);
    }
}
