#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "hvui:o:"

static FILE *input_file = NULL;
static FILE *output_file = NULL;
static uint32_t recursive_calls = 0;

//bool read_input(char *in_file, uint32_t vertices){
//input = fopen(in_file, "r"){

//}
//output = fopen(out_file, "r"){

//}
//if(input == NULL){
//	free(input);
//}
//if(output == NULL){
//	free(output);
//}
//return true;
//input = fopen(in_file, "r");
//char buf[1024];
//fgets(buf, 1024, input);
//buf[strlen(buf)-1] = '\0';
//sscanf(buf, "%u", &vertices);
//strdup
//}

/*
uint32_t number_adjacents(Graph *G, uint32_t v, uint32_t num_vertices){
	uint32_t counter = 0;
	for(uint32_t i = 0; i < num_vertices; i+=1){
		if(graph_has_edge(G, v, i)){
			counter += 1;
		}
	}
	return counter;
}
*/

bool everything_visited(Graph *G) {
    for (uint32_t i = 0; i < graph_vertices(G); i += 1) {
        if (graph_visited(G, i) == false) {
            return false;
        }
    }
    return true;
}

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile,
    bool v_flag, uint32_t vertices) {
    if (path_length(curr) == vertices) {
        if (v_flag) {
            path_print(curr, outfile, cities);
        }
        if (path_length(curr) < path_length(shortest) || path_length(shortest) == 0) {
            path_copy(shortest, curr);
        }
        //free(curr);
        //v = 0;
        //graph_mark_unvisited(G, v);
        //path_pop_vertex(curr, &v, G);
    }
    recursive_calls += 1;
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    //for(uint32_t i = 0; i < number_adjacents(G, v, num_vertices)){

    //if (path_length(curr) == vertices) {
    //    if (v_flag) {
    //        path_print(curr, outfile, cities);
    //    }
    //    if (path_length(curr) < path_length(shortest) || path_length(shortest) == 0) {
    //        path_copy(shortest, curr);
    //    }
    //free(curr);
    //v = 0;
    //graph_mark_unvisited(G, v);
    //path_pop_vertex(curr, &v, G);
    //}

    for (uint32_t j = 0; j < graph_vertices(G); j += 1) {
        if (graph_has_edge(G, v, j)) {
            if (graph_visited(G, j) == false) {
                dfs(G, j, curr, shortest, cities, outfile, v_flag, vertices);
            }
        }
    }
    //}
    //if(everything_visited){
    //print to outfile
    //check if theresa new shortest
    //}
    //if (path_length(curr) == vertices) {
    //    if (v_flag) {
    //        path_print(curr, outfile, cities);
    //    }
    //    if (path_length(curr) < path_length(shortest) || path_length(shortest) == 0) {
    //        path_copy(shortest, curr);
    //    }
    //free(curr);
    //v = 0;
    //   graph_mark_unvisited(G, v);
    //    path_pop_vertex(curr, &v, G);
    //}
    graph_mark_unvisited(G, v);
    path_pop_vertex(curr, &v, G);
}

int main(int argc, char **argv) {
    int opt = 0;
    bool no_input_flag = true;
    char *in = NULL;
    char *out = NULL;
    uint32_t vertices;
    bool h_flag = false;
    bool v_flag = false;
    bool u_flag = false;
    bool i_flag = false;
    bool o_flag = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input_flag = false;
        switch (opt) {
        case 'i':
            i_flag = true;
            in = optarg;
            break;
        case 'o':
            o_flag = true;
            out = optarg;
            break;
        case 'v': v_flag = true; break;
        case 'u': u_flag = true; break;
        case 'h':
            v_flag = false;
            u_flag = false;
            i_flag = false;
            o_flag = false;
            h_flag = true;
            break;
        }
    }
    if (h_flag == true || no_input_flag == true) {
        printf("SYNOPSIS\n");
        printf("  Travelling Salesman Problem using DFS.\n\n");
        printf("USAGE\n");
        printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
        printf("OPTIONS\n");
        printf("  -u             Use undirected graph.\n");
        printf("  -v             Enable verbose printing.\n");
        printf("  -h             Program usage and help.\n");
        printf("  -i infile      Input containing graph (default: stdin)\n");
        printf("  -o outfile     Output of computer path (default: stdout)\n");
    } else {

        if (i_flag == false) {
            input_file = stdin;
        } else {
            input_file = fopen(in, "r");
        }
        if (o_flag == false) {
            output_file = stdout;
        } else {
            output_file = fopen(out, "w+");
        }

        char vertices_line[1024];
        fgets(vertices_line, 1024, input_file);
        vertices_line[strlen(vertices_line) - 1] = '\0';
        if (1 != sscanf(vertices_line, "%u", &vertices)) {
            fprintf(stderr, "Nothing in file");
            return 1;
        }

        //printf("%" PRIu32 "\n", vertices);
        char *cities = (char *) calloc(vertices, sizeof(char));
        //char *cities[vertices];
        for (uint32_t i = 0; i < vertices; i += 1) {
            char curr_city[1024];
            fgets(curr_city, 1024, input_file);
            curr_city[strlen(curr_city) - 1] = '\0';
            //printf("%s \n", curr_city);
            char *city_copy = strdup(curr_city);
            //printf("%s \n", curr_city);
            //strcpy(cities[i], city_copy);
            cities[i] = *city_copy;
            free(city_copy);
            city_copy = NULL;
        }
        //for(uint32_t i = 0; i < vertices; i+=1){
        //	printf("%s \n", cities[i]);
        //free(cities);
        //printf("%c \n", cities[i]);
        //}
        /*

	char *cities[vertices][1024];
	for(uint32_t i = 0; i < vertices; i+=1){
		char curr_city[1024];
		fgets(curr_city, 1024, input_file);
		curr_city[strlen(curr_city)-1] = '\0';
		char* city_copy = strdup(curr_city);
		cities[i] = *city_copy;
		free(city_copy);
		city_copy = NULL;
	}
*/
        Graph *locations = graph_create(vertices, u_flag);
        if (locations == NULL) {
            fprintf(stderr, "%s", "locations in NULL\n");
            graph_delete(&locations);
            return 1;
        }

        //char curr_vertex[1024];
        while (!feof(input_file)) {
            uint32_t i = 0;
            uint32_t j = 0;
            uint32_t k = 0;
            char curr_vertex[1024];
            fgets(curr_vertex, 1024, input_file);
            curr_vertex[strlen(curr_vertex) - 1] = '\0';
            sscanf(curr_vertex, "%u %u %u", &i, &j, &k);
            graph_add_edge(locations, i, j, k);
        }

        Path *curr = path_create();
        Path *shortest = path_create();
        if (vertices == 0 || vertices == 1) {
            printf("There's nowhere to go.\n");
        } else {
            dfs(locations, START_VERTEX, curr, shortest, &cities, output_file, v_flag, vertices);
            if (v_flag == false) {
                path_print(shortest, output_file, &cities);
            }
            printf("Total recursive calls: %" PRIu32 "\n", recursive_calls);
        }
        fclose(output_file);
        fclose(input_file);
        graph_delete(&locations);
        free(cities);
    }
}
