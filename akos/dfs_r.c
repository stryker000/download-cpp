#include <stdio.h>

#define MAX 10

int stack[MAX];
int top = -1;

void push(int vertex) {
    if (top == MAX - 1)
        printf("Stack is full\n");
    else
        stack[++top] = vertex;
}

int pop() {
    if (top == -1) {
        printf("Stack is empty\n");
        return -1;
    } else
        return stack[top--];
}

int isEmpty() {
    return top == -1;
}

void DFS(int graph[MAX][MAX], int visited[MAX], int startVertex, int destinationVertex, int numVertices) {
    push(startVertex);
    visited[startVertex] = 1;

    while (!isEmpty()) {
        int node = pop();
        printf("%d ", node);

        // Check if destination is reached
        if (node == destinationVertex) {
            printf("\nDestination %d reached. Stopping DFS.\n", destinationVertex);
            return;
        }

        for (int i = 0; i < numVertices; i++) {
            if (graph[node][i] == 1 && visited[i] == 0) {
                push(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

int main() {
    int numVertices, startVertex, destinationVertex;
    int graph[MAX][MAX], visited[MAX];

    // Initialize visited array
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
    }

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the adjacency matrix for the graph:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the starting vertex for the graph: ");
    scanf("%d", &startVertex);

    printf("Enter the destination vertex for the graph: ");
    scanf("%d", &destinationVertex);

    printf("DFS traversal starting from vertex %d:\n", startVertex);
    DFS(graph, visited, startVertex, destinationVertex, numVertices);

    return 0;
}
