#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

struct item {
    int node;
    int priority;  
};

struct item pr[MAX];
int size = -1;

int graph[MAX][MAX];
int n;

void enqueue(int node, int priority) {
    size++;
    pr[size].node = node;
    pr[size].priority = priority;
}

int peek() {
    int lowestPriority = INT_MAX;
    int ind = -1;

    for (int i = 0; i <= size; i++) {
        if (pr[i].priority < lowestPriority) {
            lowestPriority = pr[i].priority;
            ind = i;
        }
    }
    return ind;
}

int dequeue() {
    int ind = peek();
    int node = pr[ind].node;

    for (int i = ind; i < size; i++) {
        pr[i] = pr[i + 1];
    }
    size--;
    return node;
}

void bestFirstSearch(int start, int goal, int heuristic[]) {
    bool visited[MAX] = { false };
    enqueue(start, heuristic[start]);
    visited[start] = true;

    printf("Best First Search Path: ");
    while (size != -1) {
        int current = dequeue();
        printf("%d ", current);

        if (current == goal) {
            printf("\nGoal Node %d found!\n", goal);
            return;
        }

        for (int i = 0; i < n; i++) {
            if (graph[current][i] != 0 && !visited[i]) {
                enqueue(i, heuristic[i]);
                visited[i] = true;
            }
        }
    }
    printf("\nGoal Node %d not reachable!\n", goal);
}

int main() {
    int startNode, goalNode;
    int edges, u, v;

    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &n);

    // Initialize adjacency matrix to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge in the format 'u v' (without quotes):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;  // If the graph is undirected
    }

    int heuristic[MAX];
    printf("Enter the heuristic values for each node:\n");
    for (int i = 0; i < n; i++) {
        printf("Heuristic for node %d: ", i);
        scanf("%d", &heuristic[i]);
    }

    printf("Enter the start node: ");
    scanf("%d", &startNode);
    printf("Enter the goal node: ");
    scanf("%d", &goalNode);

    bestFirstSearch(startNode, goalNode, heuristic);

    return 0;
}

// O(n x E)


