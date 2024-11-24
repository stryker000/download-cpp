#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool dfs(int start, int goal, vector<vector<int>>& adjList, vector<bool>& visited) {
    stack<int> s;
    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
        int node = s.top();
        s.pop();
        cout << node << " ";

        if (node == goal) {
            return true; // Stop traversal when the goal is found
        }

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                s.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    return false; 
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

    cout << "DFS traversal from node " << start << " to node " << goal << ": ";
    if (!dfs(start, goal, adjList, visited)) {
        cout << "\nGoal node " << goal << " is not reachable from node " << start << ".";
    }
    cout << endl;

    return 0;
}
