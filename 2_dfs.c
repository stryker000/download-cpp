#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int stack_arr[MAX];
int top = -1;

void push(int data) {
    if (top == MAX - 1) {
        printf("Stack is full, you can't push element\n");
        return;
    }
    top = top + 1;
    stack_arr[top] = data;
}

int pop() {
    int value;
    if (top == -1) {
        printf("Stack is empty, nothing to pop\n");
        exit(1);
    }
    value = stack_arr[top];
    top = top - 1;
    return value;
}

int isempty() {
    return top == -1;
}

void DFS(int graph[MAX][MAX], int visited[], int start, int numvertice) {
    push(start);
    visited[start] = 1;

    printf("*** DFS traversal is starting from the vertex: %d \n", start);

    while (!isempty()) {
        int node = pop();
        printf("%d \n", node);

        for (int i = 0; i < numvertice; i++) {
            if (graph[node][i] == 1 && visited[i] == 0) {
                push(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

int main() {
    int numvertice, startvertex, edges, vertex1, vertex2;
    int graph[MAX][MAX], visited[MAX];

    // Initialize visited array and adjacency matrix
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter the number of vertices: ");
    scanf("%d", &numvertice);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    // Accept edges from the user
    for (int i = 0; i < edges; i++) {
        printf("Enter edge (two vertices between 0 and %d): ", numvertice - 1);
        scanf("%d %d", &vertex1, &vertex2);

        // Mark the edge in the adjacency matrix (undirected graph)
        graph[vertex1][vertex2] = 1;
        graph[vertex2][vertex1] = 1;
    }

    printf("Enter the starting vertex for the graph: ");
    scanf("%d", &startvertex);

    DFS(graph, visited, startvertex, numvertice);

    return 0;
}
