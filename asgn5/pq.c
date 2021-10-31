#include "pq.h"

#include "node.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue{
	uint32_t head;
	uint32_t tail;
	uint32_t size;
	uint32_t capacity;
	Node **items;
};

PriorityQueue *pq_create(uint32_t capacity){
	PriorityQueue *q = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	if(q){
		q->head = 0;
		q->tail = 0;
		q->size = 0;
		q->capacity = capacity;
		q->items = (Node **) malloc(capacity *sizeof(Node *));
		if(q->items == NULL){
			free(*q);
			*q = NULL;
		}
	}
}

void pq_delete(PriorityQueue **q){
	if (*q && (*q)->items){
		free((*q)->items);
		free(*q);
		*q = NULL;
	}
	return;
}

bool pq_empty(PriorityQueue *q){
	if (q->size == 0){
		return true;
	}
	return false;
}

bool pq_full(PriorityQueue *q){
	if(q->size == q->capacity){
		return true;
	}
	return false;
}

uint32_t pq_size(PriorityQueue *q){
	return q->size;
}

static Node *get_pq_element(PriorityQueue *q, uint32_t index){
	if(!pq_empty(q) && index < q->size-1){
		return q->items[index];
	}
}

static void set_pq_element(PriorityQueue *q, uint32_t index, Node *n){
	
}

bool enqueue(PriorityQueue *q, Node *n){

}

bool dequeue(PriorityQueue *q, Node **n){
	if(pq_empty(q)){
		return false;
	}
	*n = q->items[q->head++];
	q->size--;
	return true;
}

void pq_print(PriorityQueue *q){

}
