
#include "test.h"
#include "graph.h"


void Graph_Print(graph g) {
    printf("Graph {\n");
    for (int i = 0; i < g->size; i++) {
        if (g->vertices[i] != NULL) {
            printf("  Vertex { %d |> ", g->vertices[i]->data);
            graph_arc* v = g->vertices[i]->firstarc;
            while (v != NULL) {
                printf("(%d) %d > ", v->weight, v->vertex->data);
                v = v->nextarc;
            }
            printf("|| }\n");
        }
    }
    printf("} vertices = %d, edges = %d", g->vertex_num, g->arc_num);
} 


void test_graph_create(void) {

    printf("Empty graph:  ");
    graph g = Graph_New(VERTEX_MAXNUM);
    Graph_Print(g);

    printf("\nAdd vertices and edges:  ");
    for (int i = 0; i < 7; i++)
        Graph_AddVertex(g, i);
    Graph_AddEdgeByData(g, 3, 4, 1);
    Graph_AddEdgesByData(g, 4, (int[3]){5, 1, 6}, (int[3]){1, 1, 1}, 3);
    Graph_AddEdgeByData(g, 5, 2, 1);
    Graph_AddEdgesByData(g, 0, (int[2]){5, 2}, (int[2]){1, 1}, 2);
    Graph_AddEdgesByData(g, 1, (int[2]){2, 6}, (int[2]){1, 1}, 2);
    Graph_Print(g);
}


static bool Vertex_PrintNext(graph_vertex* v) {
    return (bool) printf("%d > ", v->data);;
}

static void Vertex_PrintBefore(graph_vertex* v) {
    printf("< %d ", v->data);;
}


void test_graph_topsort(void) {
    graph g1 = Graph_FromFile("../Source/graph1.txt");
    Graph_Print(g1);
    printf("\nTopological order: ");
    TopSort(g1, Vertex_PrintNext); puts("||");
}


void test_graph_search(void) {
    /* graph 2 looks like this:
         A → D → G
         ↓ ↘ ↓
         B   E → H
         ↓   ↓
         C → F → I
    */
    graph g2 = Graph_FromFile("../Source/graph2.txt");
    Graph_Print(g2);
    printf("\nDepth First Search from %d : ", Graph_GetFirstVertexData(g2));
    Graph_DepthFirstSearch(g2, Graph_GetFirstVertex(g2), Vertex_PrintNext); puts("||");
    printf("Breadth First Search from %d : ", Graph_GetFirstVertexData(g2));
    Graph_BreadthFirstSearch(g2, Graph_GetFirstVertex(g2), Vertex_PrintNext); puts("||");
}



void test_graph_shortestpathlength(void) {
    graph g2 = Graph_FromFile("../Source/graph2.txt");
    Graph_Print(g2); putchar('\n');
    printf("The shortest path from %d to %d is %d\n", 1, 8,
           Graph_UnweightedPathLength(g2, Graph_GetVertexByData(g2, 1), Graph_GetVertexByData(g2, 8)));
    printf("The shortest path from %d to %d is %d\n", 1, 9,
           Graph_UnweightedPathLength(g2, Graph_GetVertexByData(g2, 1), Graph_GetVertexByData(g2, 9)));

    graph g3 = Graph_FromFile("../Source/graph3.txt");
    Graph_Print(g3); putchar('\n');
    printf("The shortest path from %d to %d is %d\n", 1, 8,
           Graph_WeightedPath_Dijkstra(g3, Graph_GetVertexByData(g3, 1), Graph_GetVertexByData(g3, 8)));
    printf("The shortest path from %d to %d is %d\n", 1, 7,
           Graph_WeightedPath_Dijkstra(g3, Graph_GetVertexByData(g3, 1), Graph_GetVertexByData(g3, 7)));
}

void test_graph_minimumspanningtree(void) {
    puts("Original graph: (doubly connected)");
    graph g3 = Graph_FromFile("../Source/graph3.txt");
    Graph_Print(g3); putchar('\n');

    puts("Minimum spanning tree using Kruskal algorithm:");
    graph g3_minB = Graph_MinSpanTree_Kruskal(g3);  // could use Graph_CreateDoublyConnectedByData()
    Graph_Print(g3_minB); putchar('\n');

    Graph_CreateDoublyConnectedByData(g3);
    puts("Minimum spanning tree using Prim algorithm:");
    graph g3_minA = Graph_MinSpanTree_Prim(g3);     // could use Graph_CreateDoublyConnectedByData()
    Graph_Print(g3_minA); putchar('\n');
}

