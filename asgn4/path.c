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

//this function creates the path and is based on stack create
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->length = 0;
        p->vertices = stack_create(VERTICES);
    }
    return p;
}

//this function deletes the path and is based on stack_delete
void path_delete(Path **p) {
    if (*p) {
        stack_delete(&(*p)->vertices);
        free(*p);
        *p = NULL;
    }
}

//this function pushes a vertex to the path.
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    //cant push is they arent initialized or the stack is full
    if (p == NULL || G == NULL || stack_full(p->vertices)) {
        return false;
    }
    //only add length if there is more than one element
    if (stack_empty(p->vertices) == false) {
        uint32_t last_Vertex;
        stack_peek(p->vertices, &last_Vertex);
        uint32_t edge = graph_edge_weight(G, last_Vertex, v);
        p->length = p->length + edge;
    }
    //push the vertex
    stack_push(p->vertices, v);
    return true;
}

//this function pops a vertex out of path
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    //cant pop if they arent initialized or the stack is empty
    if (p == NULL || G == NULL || stack_empty(p->vertices)) {
        return false;
    }
    //pop first so teh value is stored in v
    stack_pop(p->vertices, v);
    //decrement the length if tehre are more elements than 1
    if (stack_empty(p->vertices) == false) {
        uint32_t last_Vertex = 0;
        stack_peek(p->vertices, &last_Vertex);
        uint32_t edge = graph_edge_weight(G, last_Vertex, *v);
        p->length = p->length - edge;
    }
    return true;
}

//this function returns the number of vertices in the path
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

//this function returns the length of the path
uint32_t path_length(Path *p) {
    return p->length;
}

//this function copies a source path to a destination path
void path_copy(Path *dst, Path *src) {
    if (dst != NULL && src != NULL) {
        stack_copy(dst->vertices, src->vertices);
        dst->length = src->length;
    }
}

//prints the path
void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %" PRIu32 "\n", p->length);
    stack_print(p->vertices, outfile, cities);
}
