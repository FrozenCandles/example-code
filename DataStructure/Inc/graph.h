#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "pubdef.h"

#include "queue.h"

typedef struct graph_arc graph_arc;
typedef struct graph_vertex {
    elemtype data;
    graph_arc* firstarc;
} graph_vertex;
struct graph_arc {
    graph_vertex* vertex;
    struct graph_arc* nextarc;
    int weight;
};
typedef struct graph {
    graph_vertex** vertices;
    int vertex_num;
    int arc_num;
    int size;
} * graph;

/* faster, but vertices are not arranged in order, and may cause problems */
#define GRAPH_FROMFILE_FASTLOAD

#define VERTEX_MAXNUM 128


graph Graph_New(int max_vertices);

graph Graph_FromFile(char* filename);

/* vertex */

graph Graph_AddVertex(graph g, int data);

graph_vertex* Graph_GetVertexByData(graph g, int data);

int Graph_GetVertexIndex(graph g, graph_vertex* v);

graph_vertex* Graph_GetFirstVertex(graph g);

elemtype Graph_GetFirstVertexData(graph g);

/* edge */

graph Graph_AddEdge(graph g, graph_vertex* v_from, graph_vertex* v_to, int weight);

graph Graph_AddEdgeByData(graph g, int v_from, int v_to, int weight);

graph Graph_AddEdgesByData(graph g, int v_from, int v_to[], int weight[], int len);

/* other */

int Graph_InDegree(graph g, graph_vertex* v);

int Graph_OutDegree(graph_vertex* v);

/* algorithms */

void TopSort(graph g, bool (*collect)(graph_vertex* v));

void Graph_DepthFirstSearch(graph g, graph_vertex* v, bool (*collect)(graph_vertex*));

void Graph_BreadthFirstSearch(graph g, graph_vertex* v, bool (*collect)(graph_vertex*));

int Graph_UnweightedPathLength(graph g, graph_vertex* v, graph_vertex* w);

#endif /* __GRAPH_H__ */
