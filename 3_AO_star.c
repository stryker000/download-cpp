#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_NODES 50

typedef struct Node {
    int id;
    int heuristic;
    int expanded;
    int optimal;
    int num_children;
    int children[MAX_NODES];
    int type[MAX_NODES];
    int cost[MAX_NODES];
} Node;


Node graph[MAX_NODES];
int num_nodes, num_connections;

void inputGraph() {
    printf("Enter the number of nodes: ");
    scanf("%d", &num_nodes);

    printf("Enter node id and heuristics of each node:\n");
    for (int i = 0; i < num_nodes; i++) {
        graph[i].id = i;
        graph[i].expanded = 0;
        graph[i].optimal = 0;
        graph[i].num_children = 0;
        scanf("%d %d", &graph[i].id, &graph[i].heuristic);
    }

    printf("Enter the number of connections: ");
    scanf("%d", &num_connections);

    printf("Enter parent_id child_id cost AND/OR(1 for AND, 0 for OR):\n");

    for (int i = 0; i < num_connections; i++) {
        int parent, child, cost, type;
        scanf("%d %d %d %d", &parent, &child, &cost, &type);

        graph[parent].children[graph[parent].num_children] = child;
        graph[parent].cost[graph[parent].num_children] = cost;
        // 1 for AND, 0 for OR
        graph[parent].type[graph[parent].num_children] = type; 
        graph[parent].num_children++;
    }
}

void aoStar(int node) {
    if (graph[node].expanded) {
        return;
    }

    graph[node].expanded = 1;

    int min_heuristic = INT_MAX;
    int selected_child = -1;

    for (int i = 0; i < graph[node].num_children; i++) {
        int child = graph[node].children[i];

        if (!graph[child].expanded) {
            // Expand the child first
            aoStar(child); 
        }

        // OR connection
        if (graph[node].type[i] == 0) { 
            int current_heuristic = graph[child].heuristic + graph[node].cost[i];
            if (current_heuristic < min_heuristic) {
                min_heuristic = current_heuristic;
                selected_child = i;
            }
        } 
        // AND connection
        else if (graph[node].type[i] == 1) { 
            int total_cost = 0;

            for (int j = 0; j < graph[node].num_children; j++) {
                if (graph[node].type[j] == 1) {
                    int sibling = graph[node].children[j];
                    total_cost += graph[sibling].heuristic + graph[node].cost[j];
                }
            }
            if (total_cost < min_heuristic) {
                min_heuristic = total_cost;
                selected_child = i;
            }
        }
    }

    if (min_heuristic != INT_MAX) {
        graph[node].heuristic = min_heuristic;
        graph[node].optimal = selected_child;
    }
}

void printOptimalPath(int node) {
    printf("%d ", node);
    if (graph[node].num_children == 0) {
        // It's a leaf node
        return; 
    }

    int optimal_child = graph[node].optimal; 

    if (graph[node].type[optimal_child] == 0) {
        printOptimalPath(graph[node].children[optimal_child]);
    } 
    else if (graph[node].type[optimal_child] == 1) { 
        for (int i = 0; i < graph[node].num_children; i++) {
            if (graph[node].type[i] == 1) {
                printOptimalPath(graph[node].children[i]);
            }
        }
    }
}

int main() {
    inputGraph();
    aoStar(0);

    printf("\nUpdated Heuristics:\n");
    for (int i = 0; i < num_nodes; i++) {
        printf("Node %d: Heuristic = %d\n", i, graph[i].heuristic);
    }

    printf("\nOptimal Path: ");
    printOptimalPath(0);
    printf("\n");

    return 0;
}