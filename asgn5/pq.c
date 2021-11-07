#include "pq.h"

#include "node.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    Node **items;
};

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

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    if (q->size == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    if (q->size == q->capacity) {
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}
/*
static Node *get_pq_element(PriorityQueue *q, uint32_t index){
	if(!pq_empty(q) && index < q->size-1){
		return q->items[index];
	}
	return NULL;
}
*/
static void set_pq_element(PriorityQueue *q, uint32_t index, Node *n) {
    if (!pq_empty(q) && index < q->size - 1) {
        q->items[index] = n;
    }
}
/*
static uint32_t min_child(PriorityQueue *q, uint32_t first, uint32_t last){
	uint32_t left = 2 * first;
	uint32_t right = left + 1;
	if(right <= last && get_pq_element(q, right - 1)->frequency < get_pq_element(q, left - 1)->frequency){
		return right;
	}	
	return left;
}

static void fix_heap(PriorityQueue *q, uint32_t first, uint32_t last){
	bool found = false;
	uint32_t mother = first;
	uint32_t least = min_child(q, mother, last);
	while(mother >= floor(last/2) && !found){
		if(get_pq_element(q, mother - 1)->frequency > get_pq_element(q, least - 1)->frequency){
			Node *temp = q->items[mother - 1];
			q->items[mother - 1] = q->items[least - 1];
			q->items[least - 1] = temp;	
			mother = least;
			least = min_child(q, mother, last);
		}else{
			found = true;
		}
	}
}
*/
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

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    //*n = q->items[q->head++];
    //q->size--;
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

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->size; i += 1) {
        node_print(q->items[i]);
    }
}
