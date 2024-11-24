#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define N 6

int findMinFNode(int f[], bool visited[]) {
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < N; v++) {
        if (!visited[v] && f[v] < min) {
            min = f[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d ", j);
        return;
    }
    printPath(parent, parent[j]);
    printf("%d ", j);
}

void aStar(int graph[N][N], int h[N], int start, int goal) {
    int g[N];
    int f[N];
    bool visited[N];
    int parent[N];

    // Initialize g, f, and visited arrays
    for (int i = 0; i < N; i++) {
        g[i] = INT_MAX;
        f[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    g[start] = 0;
    f[start] = h[start];

    for (int i = 0; i < N - 1; i++) {
        int current = findMinFNode(f, visited);

        if (current == -1) break;
        visited[current] = true;

        if (current == goal) {
            printf("Shortest path: ");
            printPath(parent, goal);
            printf("\nTotal cost: %d\n", g[goal]);
            return;
        }

        for (int neighbor = 0; neighbor < N; neighbor++) {
            if (graph[current][neighbor] && !visited[neighbor]) {
                int tempG = g[current] + graph[current][neighbor];

                if (tempG < g[neighbor]) {
                    g[neighbor] = tempG;
                    f[neighbor] = g[neighbor] + h[neighbor];
                    parent[neighbor] = current;
                }
            }
        }
    }

    printf("No path found\n");
}

int main() {
    int graph[N][N] = {0};  // Initialize graph with 0s
    int h[N];
    int start, goal;
    int edges, u, v, cost;

    // Input edges and their costs
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge in the format 'u v cost' (directed graph):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &cost);
        graph[u][v] = cost;
    }

    // Input the heuristic values
    printf("Enter the heuristic values for each node:\n");
    for (int i = 0; i < N; i++) {
        printf("Heuristic for node %d: ", i);
        scanf("%d", &h[i]);
    }

    // Input start and goal nodes
    printf("Enter the start node (0-%d): ", N - 1);
    scanf("%d", &start);
    printf("Enter the goal node (0-%d): ", N - 1);
    scanf("%d", &goal);

    // Run A* algorithm
    aStar(graph, h, start, goal);

    return 0;
}
