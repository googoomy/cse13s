#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

//CITE: This function was given by Prof. Darrell Long
struct Path {
    //the vertices comprising the path
    Stack *vertices;
    //the total length of the path
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->length = 0;
        p->vertices = stack_create(VERTICES);
        //if(!p->vertices){
        //	free(p);
        //	p = NULL;
        //}
    }
    return p;
}

void path_delete(Path **p) {
    if (*p) {
        stack_delete(&(*p)->vertices);
        free(*p);
        *p = NULL;
    }
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (p == NULL || G == NULL || stack_full(p->vertices)) {
        return false;
    }
    if (stack_empty(p->vertices) == false) {
        uint32_t last_Vertex;
        stack_peek(p->vertices, &last_Vertex);
        p->length += graph_edge_weight(G, v, last_Vertex);
    }
    bool successful_Push = stack_push(p->vertices, v);
    return successful_Push;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (p == NULL || G == NULL || stack_empty(p->vertices)) {
        return false;
    }
    bool successful_Pop = stack_pop(p->vertices, v);
    if (stack_empty(p->vertices) == false) {
        uint32_t last_Vertex = 0;
        stack_peek(p->vertices, &last_Vertex);
        p->length -= graph_edge_weight(G, *v, last_Vertex);
    }
    return successful_Pop;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    if (dst != NULL && src != NULL) {
        stack_copy(dst->vertices, src->vertices);
        dst->length = src->length;
    }
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %" PRIu32 "\n", p->length);
    stack_print(p->vertices, outfile, cities);
}
