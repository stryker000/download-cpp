#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_V 10 

void printSolution(int color[], char colors[][10], int V) {
    printf("Solution Exists: Following are the assigned colors\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d -> %s\n", i, colors[color[i] - 1]);
}


bool isSafe(int v, bool graph[MAX_V][MAX_V], int color[], int c, int V) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i]) // Check  adjacent vertices have same color
            return false;
    return true;
}

// A backtracking
bool graphColoringUtil(bool graph[MAX_V][MAX_V], int m, int color[], int v, int V, char colors[][10]) {
    if (v == V)
        return true;

    
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c, V)) {
            color[v] = c; // Assign color c to vertex v

            
            if (graphColoringUtil(graph, m, color, v + 1, V, colors))
                return true;

            color[v] = 0; 
        }
    }

    return false; 
}


bool graphColoring(bool graph[MAX_V][MAX_V], int m, int V, char colors[][10]) {
    int color[MAX_V] = {0}; 

    
    if (!graphColoringUtil(graph, m, color, 0, V, colors)) {
        printf("Solution does not exist\n");
        return false;
    }

    printSolution(color, colors, V); 
    return true;
}

int main() {
    int V; 
    int m;  

    
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    
    bool graph[MAX_V][MAX_V];
    
    printf("Enter the adjacency matrix of the graph (1 for edge, 0 for no edge):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", (int*)&graph[i][j]);
        }
    }

    
    printf("Enter the number of colors: ");
    scanf("%d", &m);

    
    char colors[MAX_V][10]; 
    printf("Enter the names of %d colors:\n", m);
    for (int i = 0; i < m; i++) {
        printf("Color %d: ", i + 1);
        scanf("%s", colors[i]);
    }

    
    graphColoring(graph, m, V, colors);

    return 0;
}