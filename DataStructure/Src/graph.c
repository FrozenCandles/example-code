
#include "graph.h"


graph Graph_FromFile(char* filename) {
#ifndef GRAPH_FROMFILE_FASTLOAD
    char line[1024];
    char* line_ptr = (char*) line;
    graph g = Graph_New(VERTEX_MAXNUM);

    char ch;
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
        error("Could not open file");
    while ((ch = (char) getc(fp)) != EOF) {
        if (ch != '\n') {
            *line_ptr = ch;
            line_ptr++;
        }
        else {
            *line_ptr = '\0';
            line_ptr = (char*) line;
            char* next_data;
            int vertex_data = (int) strtol(line_ptr, &next_data, 10);
            Graph_AddVertex(g, vertex_data);
        }
    }
    fclose(fp);

    fp = fopen(filename, "r");
    while ((ch = (char) getc(fp)) != EOF) {
        if (ch != '\n') {
            *line_ptr = ch;
            line_ptr++;
        }
        else {
            *line_ptr = '\0';
            line_ptr = (char*) line;
            char* next_data;
            int vertex_data = (int) strtol(line_ptr, &next_data, 10);
            int edge, edge_weight;
            while (sscanf(next_data, " (%d)%d", &edge_weight, &edge) == 2) {
                Graph_AddEdgeByData(g, vertex_data, edge, edge_weight);
                while (*(++next_data) != ' ');
            }
        }
    }
    fclose(fp);
    return g;
#else
    char line[1024];
    char* line_ptr = (char*) line;
    graph g = Graph_New(VERTEX_MAXNUM);

    char ch;
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
        error("Could not open file");
    while ((ch = (char) getc(fp)) != EOF) {
        if (ch != '\n') {
            *line_ptr = ch;
            line_ptr++;
        }
        else {
            *line_ptr = '\0';
            line_ptr = (char*) line;

            char* next_data;
            int vertex_data = (int) strtol(line_ptr, &next_data, 10);
            int edge, edge_weight;
            if (!Graph_GetVertexByData(g, vertex_data))
                Graph_AddVertex(g, vertex_data);
            while (sscanf(next_data, " (%d)%d", &edge_weight, &edge) == 2) {

                if (!Graph_GetVertexByData(g, edge))
                    Graph_AddVertex(g, edge);

                Graph_AddEdgeByData(g, vertex_data, edge, edge_weight);
                while (*(++next_data) != ' ')
                    if (*next_data == 0)
                        break;
            }
        }
    }
    fclose(fp);
    return g;
#endif
}


graph Graph_New(int max_vertices) {
    graph g = malloc(sizeof(graph_vertex));
    if (g == NULL)
        error("out of memory");
    g->size = max_vertices;
    g->vertices = malloc(sizeof(graph_vertex*) * g->size);
    if (g->vertices == NULL)
        error("out of memory");

    memset(g->vertices, 0, sizeof(graph_vertex*) * g->size);
    //for (int i = 0; i < g->size; i++)
    //    g->vertices[i] = NULL;
    g->vertex_num = g->arc_num = 0;
    return g;
}

graph Graph_AddVertex(graph g, int data) {
    for (int i = 0; i < g->size; i++)
        if (g->vertices[i] == NULL) {
            g->vertices[i] = malloc(sizeof(graph_vertex));
            if (g->vertices[i] == NULL)
                error("out of memory");
            g->vertices[i]->firstarc = NULL;
            g->vertices[i]->data = data;
            break;
        }
    g->vertex_num++;
    return g;
}

graph_vertex* Graph_GetVertexByData(graph g, int data) {
    for (int i = 0; i < g->size; i++)
        if (g->vertices[i] && g->vertices[i]->data == data)
            return g->vertices[i];
    return NULL;
}

graph Graph_AddEdge(graph g, graph_vertex* v_from, graph_vertex* v_to, int weight) {
    if (v_from == NULL || v_to == NULL)
        return g;
    if (v_from->firstarc == NULL) {
        graph_arc* edge = malloc(sizeof(graph_arc));
        if (edge == NULL)
            error("out of memory");
        edge->vertex = v_to;
        edge->weight = weight;
        edge->nextarc = NULL;
        v_from->firstarc = edge;
    }
    else {
        graph_arc* arc = v_from->firstarc;
        while (arc != NULL && arc->vertex != v_to) {
            if (arc->nextarc == NULL) {
                graph_arc* edge = malloc(sizeof(graph_arc));
                if (edge == NULL)
                    error("out of memory");
                edge->vertex = v_to;
                edge->weight = weight;
                edge->nextarc = NULL;
                arc->nextarc = edge;
            }
            arc = arc->nextarc;
        }
    }
    g->arc_num++;
    return g;
}

graph Graph_AddEdgeByData(graph g, int v_from, int v_to, int weight) {
    Graph_AddEdge(g,
        Graph_GetVertexByData(g, v_from),
        Graph_GetVertexByData(g, v_to),
        weight
    );
    return g;
}

graph Graph_AddEdgesByData(graph g, int v_from, int v_to[], int weight[], int len) {
    for (int i = 0; i < len; i++)
        Graph_AddEdge(g,
            Graph_GetVertexByData(g, v_from),
            Graph_GetVertexByData(g, v_to[i]),
            weight[i]
        );
    return g;
}


int Graph_InDegree(graph g, graph_vertex* v) {
    if (g == NULL || v == NULL)
        return -1;
    int indegree = 0;
    for (int i = 0; i < g->size; i++)
        if (g->vertices[i])
            for (graph_arc *arc = g->vertices[i]->firstarc; arc; arc = arc->nextarc)
                if (arc->vertex == v)
                    indegree++;

    return indegree;
}


int Graph_OutDegree(graph_vertex* v) {
    if (v == NULL)
        return -1;
    int outdegree = 0;
    for (graph_arc *arc = v->firstarc; arc; arc = arc->nextarc)
        outdegree++;
    return outdegree;
}


int Graph_GetVertexIndex(graph g, graph_vertex* v) {
#if 1
    for (int i = 0; i < g->size; i++)
        if (g->vertices[i] == v)
            return i;
    return -1;

#elif 1
    return v ? v->data : -1;

#else
    return (v - g->vertices[0]) / sizeof(graph_vertex*);
#endif
}


void Graph_GatherInDegree(graph g, int indegree[]) {
    for (int i = 0; i < g->size; i++)
        if (g->vertices[i])
            for (graph_arc *arc = g->vertices[i]->firstarc; arc; arc = arc->nextarc)
                indegree[Graph_GetVertexIndex(g, arc->vertex)]++;
        else
            indegree[i] = -1;
}



void TopSort(graph g, bool (*collect)(graph_vertex*)) {
    int indegree[VERTEX_MAXNUM];
    memset(&indegree, 0, sizeof indegree);
    Graph_GatherInDegree(g, indegree);

    queue q = Queue_New(VERTEX_MAXNUM);
    for (int i = 0; i < g->size; i++)
        if (indegree[i] == 0)
            Queue_Enqueue(q, g->vertices[i]->data);

    int counter = 0;
    while (!Queue_IsEmpty(q)) {
        graph_vertex* v = Graph_GetVertexByData(g, Queue_Dequeue(q));
        if (!collect(v))
            return;
        counter++;
        for (graph_arc* arc = v->firstarc; arc; arc = arc->nextarc) {
            graph_vertex* w = arc->vertex;
            if (--indegree[Graph_GetVertexIndex(g, w)] == 0)
                Queue_Enqueue(q, w->data);
        }
    }
    if (counter != g->vertex_num)
        warning("Graph has a cycle");

    Queue_Delete(q);
}


graph_vertex* Graph_GetFirstVertex(graph g) {
    return g->vertices[0];
}

elemtype Graph_GetFirstVertexData(graph g) {
    return g->vertices[0]->data;
}


static void _Graph_DepthFirstSearch(graph g, graph_vertex* v, bool visited[], bool (*collect)(graph_vertex*)) {
    visited[v->data] = true;
    for (graph_arc* arc = v->firstarc; arc; arc = arc->nextarc) {
        graph_vertex* w = arc->vertex;
        if (!visited[w->data]) {
            if (!collect(w))
                return;
            _Graph_DepthFirstSearch(g, w, visited, collect);
        }
    }
}


void Graph_DepthFirstSearch(graph g, graph_vertex* v, bool (*collect)(graph_vertex*)) {
    bool visited[g->size];
    memset(visited, 0, sizeof visited);
    _Graph_DepthFirstSearch(g, v, visited, collect);
}


void Graph_BreadthFirstSearch(graph g, graph_vertex* v, bool (*collect)(graph_vertex*)) {
    bool visited[g->size];
    memset(visited, 0, sizeof visited);
    queue q = Queue_New(VERTEX_MAXNUM);

    if (!visited[v->data]) {
        visited[v->data] = true;
        Queue_Enqueue(q, v->data);
        while (!Queue_IsEmpty(q)) {
            graph_vertex* w = Graph_GetVertexByData(g, Queue_Dequeue(q));
            for (graph_arc* arc = w->firstarc; arc; arc = arc->nextarc) {
                if (!visited[arc->vertex->data]) {
                    visited[arc->vertex->data] = true;
                    if (!collect(arc->vertex)) {
                        Queue_Delete(q);
                        return;
                    }
                    Queue_Enqueue(q, arc->vertex->data);
                }
            }
        }
    }
    Queue_Delete(q);
}


int Graph_UnweightedPathLength(graph g, graph_vertex* v, graph_vertex* w) {
    int dist[g->size];
    memset(dist, -1, sizeof dist);
    dist[v->data] = 0;

    queue q = Queue_New(VERTEX_MAXNUM);
    Queue_Enqueue(q, v->data);
    while (!Queue_IsEmpty(q)) {
        graph_vertex* u = Graph_GetVertexByData(g, Queue_Dequeue(q));
        for (graph_arc* arc = u->firstarc; arc; arc = arc->nextarc) {
            graph_vertex* adj = arc->vertex;
            if (dist[adj->data] == -1) {
                dist[adj->data] = dist[u->data] + 1;
                if (adj == w) {
                    Queue_Delete(q);
                    return dist[adj->data];
                }
                Queue_Enqueue(q, adj->data);
            }
        }
    }
    Queue_Delete(q);
    return -1;
}


int Graph_WeightedPath_Dijkstra(graph g, graph_vertex* v, graph_vertex* w) {
    bool visited[VERTEX_MAXNUM];
    int minpathlen[VERTEX_MAXNUM];
    memset(visited, 0, sizeof visited);
    for (int i = 0; i < VERTEX_MAXNUM; i++) minpathlen[i] = INT_MAX;

    minpathlen[v->data] = 0;
    for (int i = 0; i < g->size; i++) {
        if (!g->vertices[i]) continue;
        int minv = 0;
        int minlen = INT_MAX;

        for (int j = 0; j < g->size; j++)
            if (!visited[j] && minpathlen[j] < minlen) {
                minv = j;
                minlen = minpathlen[minv];
            }
        visited[minv] = true;
        graph_vertex* v_k = Graph_GetVertexByData(g, minv);
        for (graph_arc* arc = v_k->firstarc; arc; arc = arc->nextarc) {
            graph_vertex* u = arc->vertex;
            if (!visited[u->data] && (minlen + arc->weight < minpathlen[u->data]))
                minpathlen[u->data] = minlen + arc->weight;
        }
    }
    return minpathlen[w->data];
}



void Graph_CreateDoublyConnectedByData(graph g) {
    linkedstack list_V = LinkedStack_New();
    linkedstack list_E = LinkedStack_New();
    linkedstack list_W = LinkedStack_New();
    for (int i = 0; i < g->size; i++)
        if (g->vertices[i])
            for (graph_arc* arc = g->vertices[i]->firstarc; arc; arc = arc->nextarc) {
                LinkedStack_Push(list_V, g->vertices[i]->data);
                LinkedStack_Push(list_E, arc->vertex->data);
                LinkedStack_Push(list_W, arc->weight);
            }
    while (!LinkedStack_IsEmpty(list_V)) {
        Graph_AddEdgeByData(g,
                            LinkedStack_Top(list_E),
                            LinkedStack_Top(list_V),
                            LinkedStack_Top(list_W));
        LinkedStack_Pop(list_V);
        LinkedStack_Pop(list_E);
        LinkedStack_Pop(list_W);
    }
    LinkedStack_Delete(list_V);
    LinkedStack_Delete(list_E);
    LinkedStack_Delete(list_W);
}


graph Graph_MinSpanTree_Prim(graph g) {
#if 0
    bool isintree[VERTEX_MAXNUM];
    memset(isintree, 0, sizeof isintree);

    graph m = Graph_New(VERTEX_MAXNUM);
    for (int i = 0; i < g->size; i++)
        if (g->vertices[i])
            Graph_AddVertex(m, g->vertices[i]->data);

    isintree[g->vertices[0]->data] = true;
    for (int _ = 0; _ < g->size; _++) {  // loop N times
        int min_arc_from = -1;
        int min_arc_to = -1;
        int min_len = INT_MAX;
        for (int i = 0; i < g->size; i++)
            if (g->vertices[i] && isintree[g->vertices[i]->data])
                for (graph_arc* arc = g->vertices[i]->firstarc; arc; arc = arc->nextarc) {
                    graph_vertex *u = arc->vertex;
                    if ((!isintree[u->data] && arc->weight < min_len)) {
                        min_len = arc->weight;
                        min_arc_from = g->vertices[i]->data;
                        min_arc_to = arc->vertex->data;
                    }
                }
        if (min_arc_to != -1) {
            isintree[min_arc_to] = true;
            Graph_AddEdgeByData(m, min_arc_from, min_arc_to, min_len);
        }
    }
    return m;
#else
    int minpathfrom[g->size];
    int minpathlen[g->size];
    memset(minpathfrom, -1, sizeof minpathfrom);
    for (int i = 0; i < g->size; i++) minpathlen[i] = INT_MAX;

    // create graph with single vertices
    graph m = Graph_New(VERTEX_MAXNUM);
    for (int i = 0; i < g->size; i++)
        if (g->vertices[i])
            Graph_AddVertex(m, g->vertices[i]->data);

    int min_vtx = g->vertices[0]->data;
    for (graph_arc* arc = g->vertices[0]->firstarc; arc; arc = arc->nextarc) {
        minpathfrom[arc->vertex->data] = min_vtx;
        minpathlen[arc->vertex->data] = arc->weight;
    }
    minpathlen[min_vtx] = 0;  // put it in the tree

    for (int i = 1; i < g->size; i++) {
        if (!g->vertices[i])
            continue;

        int min_len = INT_MAX;   // find the closest vertex
        for (int j = 0; j < g->size; j++)
            if (minpathlen[j] != 0 && minpathlen[j] < min_len) {
                min_len = minpathlen[j];
                min_vtx = j;
            }

        /* put it in the tree */
        minpathlen[min_vtx] = 0;
        Graph_AddEdgeByData(m, Graph_GetVertexByData(g, minpathfrom[min_vtx])->data, Graph_GetVertexByData(g, min_vtx)->data, min_len);

        /* update adjacent vertex */
        for (graph_arc* arc = Graph_GetVertexByData(g, min_vtx)->firstarc; arc; arc = arc->nextarc)
            if (minpathlen[arc->vertex->data] != 0 && arc->weight < minpathlen[arc->vertex->data]) {
                minpathfrom[arc->vertex->data] = min_vtx;
                minpathlen[arc->vertex->data] = arc->weight;
            }
    }
    return m;
#endif
}


struct _graph_arc {
    int from;
    int to;
    int weight;
};

static int CompareByWeight(const void* a,const void* b) {
    return ((struct _graph_arc*)a)->weight - ((struct _graph_arc*)b)->weight;
}

/**
 * @brief
 * use directed graph to represent undirected graph
 * @param g
 * @return
 */
graph Graph_MinSpanTree_Kruskal(graph g) {

    struct _graph_arc arcs[g->arc_num];
    memset(arcs, 0, sizeof arcs);
    int arcs_ptr = 0;
    int conn_mark[g->size];
    for (int i = 0; i < g->size; i++) conn_mark[i] = i;

    // create graph with single vertices, and collect arcs
    graph m = Graph_New(VERTEX_MAXNUM);
    for (int i = 0; i < g->size; i++)
        if (g->vertices[i]) {
            Graph_AddVertex(m, g->vertices[i]->data);
            for (graph_arc* arc = g->vertices[i]->firstarc; arc; arc = arc->nextarc)
                arcs[arcs_ptr++] = (struct _graph_arc) {
                    .from=g->vertices[i]->data, .to=arc->vertex->data, .weight=arc->weight };
        }
    qsort(arcs, g->arc_num, sizeof(struct _graph_arc), CompareByWeight);

    int arcs_inserted = 0;
    for (int i = 0; i < g->arc_num; i++) {
        /* make sure no cycle will be added */
        if (conn_mark[arcs[i].from] != conn_mark[arcs[i].to]) {
            /* insert edge to tree */
            graph_vertex* v = Graph_GetVertexByData(m, arcs[i].from);
            graph_vertex* w = Graph_GetVertexByData(m, arcs[i].to);
            Graph_AddEdge(m, v, w, arcs[i].weight);
            Graph_AddEdge(m, w, v, arcs[i].weight);
            /* union sets between edge */
            for (int k = 0; k < g->vertex_num; k++)
                if (conn_mark[k] == conn_mark[arcs[i].to])
                    conn_mark[k] = conn_mark[arcs[i].from];

            arcs_inserted++;

            if (arcs_inserted == g->vertex_num - 1)  // minimum spanning tree has created
                break;
        }
    }


    return m;
}




