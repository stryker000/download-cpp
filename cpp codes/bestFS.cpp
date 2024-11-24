#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

struct Graph
{
    int no_vertex;
    vector<vector<pair<int, int>>> adjList; 
};

Graph *createGraph(int size)
{
    Graph *graph = new Graph();
    graph->no_vertex = size;
    graph->adjList.resize(size);
    return graph;
}

void addEdge(Graph *graph, int src, int dest, int cost)
{
    graph->adjList[src].emplace_back(dest, cost);
    graph->adjList[dest].emplace_back(src, cost); 
}

void bestfs(Graph *graph, int src, int dest, vector<double> &heuristics)
{
    int n = graph->no_vertex;
    vector<int> parent(n, -1); 

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> visited(n, 0); 

    pq.push({heuristics[src], src});
    visited[src] = 1;

    while (!pq.empty())
    {
        int curr = pq.top().second;
        pq.pop();

        cout << curr << " "; 

        if (curr == dest)
        {
            break;
        }

        for (auto neighbor : graph->adjList[curr])
        {
            int nextNode = neighbor.first;
            int cost = neighbor.second;

            if (!visited[nextNode])
            {
                pq.push({heuristics[nextNode], nextNode});
                parent[nextNode] = curr; 
                visited[nextNode] = 1;
            }
        }
    }
    cout << endl;
}

int main()
{
    int numNodes;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    Graph *graph = createGraph(numNodes);

    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter the edges (format: start_node end_node cost):" << endl;
    for (int i = 0; i < numEdges; ++i)
    {
        int u, v, cost;
        cin >> u >> v >> cost;
        addEdge(graph, u, v, cost);
    }

    vector<double> heuristics(numNodes);
    cout << "Enter the heuristic values for each node:" << endl;
    for (int i = 0; i < numNodes; ++i)
    {
        cout << "Heuristic value for node " << i << ": ";
        cin >> heuristics[i];
    }

    int start, goal;
    cout << "Enter the start node: ";
    cin >> start;
    cout << "Enter the goal node: ";
    cin >> goal;

    cout << "Optimal Path: ";
    bestfs(graph, start, goal, heuristics);

    delete graph;
    return 0;
}