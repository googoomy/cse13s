#James Gu 
#jjgu
#Fall 2021
#Assignment 4: Perambulations of Denver Long
##DESCRIPTION OF PROGRAM: The goal of this program is to find the shortest path to travers every location on a map only once when given an n by n matrix. This shortest path is called a Hamiltonian Path. Each location is called a vertex and each edge between the vertices holds a different weight. These vertices and edges are used to represent the graph. The paths can be either directed or undirected. For example, an undirected path means a point a can go to a point b and vice versa. But a directed graph means a can go to b but b cant necessarily go to a.

###BUILD FOR PROGRAM: this program needs the following:graph.c, graph.h, stack.c, stack.h, path.c, path.h, vertices.h, tsp.c, Makefile, README.md, DESIGN.pdf

####USER GUIDE: The first step to use this program is to use the command make. This will compile the program and allow you to press ./tsp. doing ./tsp or ./tsp -h will bring up the user manual to get a description of the program and also other commands. These commands include -i to specify an input file, -o to specify and output file, -v to make the output verbose, and -u to turn on undirected graph.
