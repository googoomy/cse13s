#include "graph.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


//CITE: This function was given by Prof. Darrell Long
struct Graph{
	//number of vertices
	uint32_t vertices;
	//undirected graph?
	bool undirected;
	//where have we gone?
	bool visited[VERTICES];
	//adjacency matrix
	uint32_t matrix[VERTICES][VERTICES];
};

//CITE: This function was given by Prof. Darrell Long
Graph *graph_create(uint32_t vertices, bool undirected){
	Graph *G = (Graph *)calloc(1, sizeof(Graph));
	G->vertices = vertices;
	G->undirected = undirected;
	return G;
}

//CITE: This function was given by Prof. Darrell Long
void graph_delete(Graph **G){
	free(*G);
	*G = NULL;
	return;
}

uint32_t graph_vertices(Graph *G){
	return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k){
	if(i >= G->vertices || j >= G->vertices){
		return false;
	}	
	G->matrix[i][j] = k;
	if(G->undirected){
		G->matrix[j][i] = k;
	}
	return true;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j){
	if(i < G->vertices && j < G->vertices && G->matrix[i][j] > 0){
		return true;
	}
	return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j){
	if(graph_has_edge(&G, i, j)){
		return G->matrix[i][j];
	}else{
		return 0;
	}
}

bool graph_visited(Graph *G, uint32_t v){
	if(G->visited[v]){
		return true;
	}
	return false;
}

void graph_mark_visited(Graph *G, uint32_t v){
	if(v < VERTICES){
		G->visited[v] = true;
	}
}

void graph_mark_unvisited(Graph *G, uint32_t v){
	if(v < VERTICES){
		G->visited[v] = false;
	}
}

void graph_print(Graph *G){
	for (uint32_t i = 0; i < G->vertices; i+=1){
		for(uint32_t j = 0; j < G->vertices; j+=1){
			printf("%" PRIu32 " ", G->matrix[i][j]);
		}
		printf("/n");
	}
	for (uint32_t k = 0; k < G->vertices; k += 1){
		printf("%" PRIu32 " ", G->visited[k]);
	}
}



