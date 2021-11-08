#include "pq.h"

#include "node.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//struct for the pq
//This was given by TA Christian
struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    Node **items;
};

//The constructor for pq
//pseudocode was given from TA Christian
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (Node **) malloc(capacity * sizeof(Node *));
        if (q->items == NULL) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

//This deletes the priority queue
//inspired from the stack_delete from asgn3
void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

//return true if the pq is empty and false otherwise
bool pq_empty(PriorityQueue *q) {
    if (q->size == 0) {
        return true;
    }
    return false;
}

//returns true if the pq is full and false otherwise
bool pq_full(PriorityQueue *q) {
    if (q->size == q->capacity) {
        return true;
    }
    return false;
}

//returns the size of pq
uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

//helper function that sets an element in pq to a node that is passed through
//given by TA Christian
static void set_pq_element(PriorityQueue *q, uint32_t index, Node *n) {
    if (!pq_empty(q) && index < q->size - 1) {
        q->items[index] = n;
    }
}

//Enqueues a node into the pq
bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }
    set_pq_element(q, q->tail, n);
    q->tail += 1;
    //fix_heap(q, head, tail);
    q->size += 1;
    return true;
}

//passes the smallest node to *n
bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    uint32_t temp = 0;
    for (uint32_t i = 0; i < q->size; i += 1) {
        if ((q->items[temp])->frequency >= (q->items[i])->frequency) {
            temp = i;
        }
    }
    *n = q->items[temp];
    for (uint32_t i = temp; i < q->size; i += 1) {
        q->items[i] = q->items[i + 1];
    }
    q->size -= 1;
    return true;
}

//prints out the pq
void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->size; i += 1) {
        node_print(q->items[i]);
    }
}
