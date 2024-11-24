#include <iostream>
#include <vector>

using namespace std;

#define MAX 100

int adj_mat[MAX][MAX];
int color[MAX];
int num_vertices, num_edges;

bool isValid(int vertex, int c) 
{
    for (int i = 1; i <= num_vertices; i++)  
    {
        if (adj_mat[vertex][i] && color[i] == c) 
        { 
            return false;
        }
    }
    return true;
}

bool ColorGraph(int vertex, int cm) 
{
    if (vertex > num_vertices)  
        return true;

    for (int c = 1; c <= cm; c++) 
    {
        if (isValid(vertex, c)) 
        {
            color[vertex] = c;

            if (ColorGraph(vertex + 1, cm)) 
                return true;

            color[vertex] = 0;
        }
    }

    return false;
}

bool CheckGraphColoring(int cm) 
{
    for (int i = 1; i <= num_vertices; i++)  
        color[i] = 0;  

    if (ColorGraph(1, cm))  
        return true;
    else
        return false;
}

void printSolution() 
{
    cout << "Solution: Following are the assigned colors for each vertex:" << endl;
    for (int i = 1; i <= num_vertices; i++)  
    {
        cout << "Vertex " << i << " ---> Color " << color[i] << endl;
    }
}

int main() 
{
    int cm;  
    int src, dest;

    cout << "Enter the number of nodes: ";
    cin >> num_vertices;

    cout << "Enter the number of edges: ";
    cin >> num_edges;

    for (int i = 0; i < num_edges; i++) 
    {
        cout << "\nEnter edge " << i + 1 << " (source -> destination): ";
        cin >> src >> dest;
        adj_mat[src][dest] = 1;
        adj_mat[dest][src] = 1;
    }

    cout << "Enter the number of colors: ";
    cin >> cm;

    if (CheckGraphColoring(cm))
        printSolution();
    else 
        cout << "Solution does not exist for the given number of colors." << endl;

    return 0;
}
