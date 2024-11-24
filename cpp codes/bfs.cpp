#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool bfs(int start, int goal, vector<vector<int>>& adjList, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        if (node == goal) {
            return true; // Stop traversal when the goal is found
        }

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    return false; // Return false if goal is not reachable
}

int main() {
    int n, e;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> e;

    vector<vector<int>> adjList(n);
    vector<bool> visited(n, false);

    cout << "Enter the edges (u v):\n";
    for (int i = 0; i < e; ++i) {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u); 
    }

    int start, goal;
    cout << "Enter the starting node: ";
    cin >> start;
    cout << "Enter the goal node: ";
    cin >> goal;

    cout << "BFS traversal from node " << start << " to node " << goal << ": ";
    if (!bfs(start, goal, adjList, visited)) {
        cout << "\nGoal node " << goal << " is not reachable from node " << start << ".";
    }
    cout << endl;

    return 0;
}
