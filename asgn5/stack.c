#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//This entire program is based on assignment 3's stack.c
//This was given in the asgn 3 doc
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

//This is the constructor for stack
//Credit: my asgn3
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) malloc(capacity * sizeof(Node *));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

//This is teh destructor for stack
//Credit:my asgn3
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

//This function returns true if the stack is empty and false otherwise
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

//this function returns true if the stack is full and false otherwise
bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}

//This function outputs the size of the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

//this function pushes a node to the top of the stack
bool stack_push(Stack *s, Node *n) {
    if (s == NULL || stack_full(s) == true) {
        return false;
    }
    s->items[s->top] = n;
    s->top += 1;
    return true;
}

//this pops the first node out of the top of the stack
bool stack_pop(Stack *s, Node **n) {
    if (s == NULL || stack_empty(s) == true) {
        return false;
    }
    s->top -= 1;
    *n = s->items[s->top];
    return true;
}

//this function prints the stack
void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        node_print(s->items[i]);
    }
}
