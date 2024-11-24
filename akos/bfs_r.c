#include <stdio.h>

#define MAX 10 

int adjMatrix[MAX][MAX];  
int visited[MAX]; 
int queue[MAX];  
int front = -1, rear = -1;

void enqueue(int vertex) {
    if (rear == MAX - 1)
        printf("Queue is full\n");
    else {
        if (front == -1)  
            front = 0;
        rear++;
        queue[rear] = vertex;
    }
}

int dequeue() {
    int vertex;
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return -1;
    } else {
        vertex = queue[front];
        front++;
        return vertex;
    }
}

void bfs(int startVertex, int destinationVertex, int n) {
    int i;
    
    enqueue(startVertex);
    visited[startVertex] = 1;  

    while (front <= rear) {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        // Check if the destination is reached
        if (currentVertex == destinationVertex) {
            printf("\nDestination %d reached. Stopping BFS.\n", destinationVertex);
            return;
        }

        for (i = 0; i < n; i++) {
            if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int n, i, j, startVertex, destinationVertex;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Input adjacency matrix
    printf("Enter the adjacency matrix (0 or 1):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &adjMatrix[i][j]);
        }
        visited[i] = 0;  // Initialize visited array to 0
    }

    printf("Enter the starting vertex (0 to %d): ", n - 1);
    scanf("%d", &startVertex);

    printf("Enter the destination vertex (0 to %d): ", n - 1);
    scanf("%d", &destinationVertex);

    printf("BFS traversal starting from vertex %d:\n", startVertex);
    bfs(startVertex, destinationVertex, n);

    return 0;
}
