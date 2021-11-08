#include "code.h"

#include "defines.h"

#include <inttypes.h>
#include <stdio.h>

//constructer function for making code.
//pseudo given from TA Christian
Code code_init(void) {
    Code c = { .top = 0, .bits = { 0 } };
    return c;
}

//returns the size of the Code
uint32_t code_size(Code *c) {
    return c->top;
}

//returns true if Code is empty and false otherwise
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

//returns true if Code is fill and false otherwise
bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    }
    return false;
}

//Sets the bit at index i in the Code to 1.
//Pseudocode given by TA Christian
bool code_set_bit(Code *c, uint32_t i) {
    if (i < ALPHABET) {
        c->bits[i / 8] = 1;
        return true;
    }
    return false;
}

//Sets the bit at index i in the Code to 0
bool code_clr_bit(Code *c, uint32_t i) {
    if (i < ALPHABET) {
        c->bits[i / 8] = 0;
        return true;
    }
    return false;
}

//Gets the bit at index i in Code
bool code_get_bit(Code *c, uint32_t i) {
    if (i < ALPHABET && c->bits[i / 8] == 1) {
        return true;
    }
    return false;
}

//Pushes bit onto Code
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    //bitwise operation was given by TA Eugene
    c->bits[c->top / 8] |= bit << (c->top % 8);
    c->top += 1;
    return true;
}

//Pops bit into bit
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    *bit = c->bits[c->top / 8] | (1 << (c->top % 8));
    //opposite of push
    c->bits[c->top / 8] &= ~(1 << (c->top % 8));
    c->top -= 1;
    return true;
}

//prints the code
void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i += 1) {
        printf("%" PRIu32, c->bits[i]);
    }
}
