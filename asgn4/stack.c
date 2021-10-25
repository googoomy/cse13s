#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//CITE:This function was given by Prof. Darrell Long
struct Stack {
    //index of the next empty slot
    uint32_t top;
    //number of items that can be pushed
    uint32_t capacity;
    //array of items, each with type uint32_t
    uint32_t *items;
};

//CITE: This function was given by Prof. Darrell Long
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

//CITE: This function was given by Prof. Darrell Long
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

//this function returns true if the stack is empty and false if not
bool stack_empty(Stack *s) {
    //if the first element is 0 then everything is 0 so it is empty
    if (s->top == 0) {
        return true;
    }
    return false;
}

//this function returns true if the stack is full and false if not
bool stack_full(Stack *s) {
    //if the top element in the stack is not 0 then everything is not 0 so it is full
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}

//this function returns the number of items on the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

//this function pushes an elemeent to the top of the stack
bool stack_push(Stack *s, uint32_t x) {
    //if the stack isnt initialized or it is full you cant push
    if (s == NULL || stack_full(s) == true) {
        return false;
    }
    //set the element top is at to x and increment top by 1
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

//this element pops an element out of the top of the stack
bool stack_pop(Stack *s, uint32_t *x) {
    //if the stack isnt initialized or the stack is empty you cant pop from the stack
    if (s == NULL || stack_empty(s) == true) {
        return false;
    }
    //the current top needs to be decremented so the last element is grabbable
    s->top -= 1;
    *x = s->items[s->top];
    //set the item we grabbed to 0 because we popped it out
    s->items[s->top] = 0;
    return true;
}

//this function only takes a peek at the top of the stack. no setting it to 0
bool stack_peek(Stack *s, uint32_t *x) {
    //if the stack is not initialized or the stack is empty theres nothing to peek at
    if (s == NULL || stack_empty(s) == true) {
        return false;
    }
    //current top needs to be decremented so teh last element is peekable
    s->top -= 1;
    *x = s->items[s->top];
    //since we just peeked and we decremented, to leave the stack as is add back 1 to top
    s->top += 1;
    return true;
}

//this function copies a source stack to destination stack
void stack_copy(Stack *dst, Stack *src) {
    //as long as the two stacks are initialized and the capacity is okay we can copy.
    if (dst != NULL && src != NULL && dst->capacity >= src->top) {
        for (uint32_t i = 0; i < src->top; i += 1) {
            dst->items[i] = src->items[i];
        }
        dst->top = src->top;
    }
}

//CITE: This function was given by prof. Darrell Long
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
