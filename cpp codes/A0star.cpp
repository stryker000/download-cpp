#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>

using namespace std;

// Function to calculate the cost for each condition (AND/OR)
map<string, int> calculateCost(map<string, int>& H, map<string, vector<string>>& condition, map<string, map<string, int>>& adj_matrix) {
    map<string, int> cost;

    if (condition.count("AND")) {
        vector<string> AND_nodes = condition["AND"];
        stringstream pathA;
        int pathA_cost = 0;

        for (size_t i = 0; i < AND_nodes.size(); ++i) {
            pathA << AND_nodes[i];
            if (i != AND_nodes.size() - 1)
                pathA << " AND ";
            pathA_cost += H[AND_nodes[i]] + adj_matrix["start"][AND_nodes[i]];  // Use weight from adjacency matrix
        }

        string pathA_str = pathA.str();
        cost[pathA_str] = pathA_cost;
    }

    if (condition.count("OR")) {
        vector<string> OR_nodes = condition["OR"];
        stringstream pathB;
        int min_cost = INT_MAX;
        string min_node;

        for (size_t i = 0; i < OR_nodes.size(); ++i) {
            pathB << OR_nodes[i];
            if (i != OR_nodes.size() - 1)
                pathB << " OR ";
            int cost_candidate = H[OR_nodes[i]] + adj_matrix["start"][OR_nodes[i]];  // Use weight from adjacency matrix
            if (cost_candidate < min_cost) {
                min_cost = cost_candidate;
                min_node = OR_nodes[i];
            }
        }

        string pathB_str = pathB.str();
        cost[pathB_str] = min_cost;
    }

    return cost;
}

// Function to update the cost of each node based on conditions
map<string, map<string, int> > updateCost(map<string, int>& H, map<string, map<string, vector<string> > >& conditions, map<string, map<string, int>>& adj_matrix) {
    vector<string> main_nodes;
    for (map<string, map<string, vector<string> > >::iterator it = conditions.begin(); it != conditions.end(); ++it)
        main_nodes.push_back(it->first);
    reverse(main_nodes.begin(), main_nodes.end());

    map<string, map<string, int> > least_cost;

    for (size_t idx = 0; idx < main_nodes.size(); ++idx) {
        string key = main_nodes[idx];
        map<string, vector<string> > condition = conditions[key];
        map<string, int> c = calculateCost(H, condition, adj_matrix);

        cout << key << ": ";
        for (map<string, vector<string> >::iterator it = condition.begin(); it != condition.end(); ++it) {
            cout << it->first << " ";
            for (size_t i = 0; i < it->second.size(); ++i)
                cout << it->second[i] << " ";
            cout << ">>> ";
        }
        for (map<string, int>::iterator it = c.begin(); it != c.end(); ++it) {
            cout << it->first << " (" << it->second << ")";
        }
        cout << endl;

        int min_cost = INT_MAX;
        for (map<string, int>::iterator it = c.begin(); it != c.end(); ++it) {
            if (it->second < min_cost) {
                min_cost = it->second;
            }
        }

        H[key] = min_cost;
        least_cost[key] = c;
    }

    return least_cost;
}

// Modified shortest path function to return both path and total weight
pair<string, int> shortestPath(string start, map<string, map<string, int> >& updated_cost, map<string, map<string, int>>& adj_matrix) {
    string path = start;
    int total_weight = 0;

    if (updated_cost.count(start)) {
        int min_cost = INT_MAX;
        string min_path;

        map<string, int>& cost_map = updated_cost[start];
        for (map<string, int>::iterator it = cost_map.begin(); it != cost_map.end(); ++it) {
            if (it->second < min_cost) {
                min_cost = it->second;
                min_path = it->first;
            }
        }

        stringstream ss(min_path);
        vector<string> next_nodes;
        string node;

        while (ss >> node) {
            if (node != "AND" && node != "OR")
                next_nodes.push_back(node);
        }

        if (next_nodes.size() == 1) {
            pair<string, int> next_path = shortestPath(next_nodes[0], updated_cost, adj_matrix);
            path += " <-- " + next_path.first;
            total_weight += adj_matrix[start][next_nodes[0]] + next_path.second;  // Add edge weight
        } else if (next_nodes.size() > 1) {
            path += " <-- (" + min_path + ") [";
            pair<string, int> next_path = shortestPath(next_nodes[0], updated_cost, adj_matrix);
            path += next_path.first;
            total_weight += adj_matrix[start][next_nodes[0]] + next_path.second;  // Add edge weight

            for (size_t i = 1; i < next_nodes.size(); ++i) {
                pair<string, int> next_path_or = shortestPath(next_nodes[i], updated_cost, adj_matrix);
                path += " + " + next_path_or.first;
                total_weight += adj_matrix[start][next_nodes[i]] + next_path_or.second;  // Add edge weight
            }
            path += "]";
        }
    }

    return make_pair(path, total_weight);
}

int main() {
    map<string, int> H;
    H["A"] = -1;
    H["B"] = 5;
    H["C"] = 2;
    H["D"] = 4;
    H["E"] = 7;
    H["F"] = 9;
    H["G"] = 3;
    H["H"] = 0;
    H["I"] = 0;
    H["J"] = 0;

    map<string, map<string, vector<string> > > conditions;
    conditions["A"]["OR"] = vector<string>{"B"};
    conditions["A"]["AND"] = vector<string>{"C", "D"};
    conditions["B"]["OR"] = vector<string>{"E", "F"};
    conditions["C"]["OR"] = vector<string>{"G"};
    conditions["C"]["AND"] = vector<string>{"H", "I"};
    conditions["D"]["OR"] = vector<string>{"J"};

    
    map<string, map<string, int>> adj_matrix;
    adj_matrix["A"]["B"] = 6;
    adj_matrix["A"]["C"] = 1;
    adj_matrix["A"]["D"] = 8;
    adj_matrix["B"]["E"] = 1;
    adj_matrix["B"]["F"] = 1;
    adj_matrix["C"]["G"] = 1;
    adj_matrix["C"]["H"] = 1;
    adj_matrix["C"]["I"] = 2;
    adj_matrix["D"]["J"] = 1;

    cout << "Updated Cost:" << endl;
    map<string, map<string, int> > updated_cost = updateCost(H, conditions, adj_matrix);
   

    cout << "Shortest Path:" << endl;
    pair<string, int> result = shortestPath("A", updated_cost, adj_matrix);
    cout << "Path: " << result.first << endl;
    cout << "Total Weight: " << result.second << endl;

    return 0;
}
