#include <iostream>
#include <vector>
#include <climits>
#include <chrono>

using namespace std;

struct Edge {
    int source, destination, weight;
};

void bellmanFord(int vertices, vector<Edge>& edges, int start) {
    vector<int> distance(vertices, INT_MAX);
    distance[start] = 0;

    for (int i = 1; i < vertices; i++) {
        for (const auto& edge : edges) {
            if (distance[edge.source] != INT_MAX && 
                distance[edge.source] + edge.weight < distance[edge.destination]) {
                distance[edge.destination] = distance[edge.source] + edge.weight;
            }
        }
    }

    for (const auto& edge : edges) {
        if (distance[edge.source] != INT_MAX && 
            distance[edge.source] + edge.weight < distance[edge.destination]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    cout << "Vertex Distance from Source:" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << i << "\t\t" << distance[i] << endl;
    }
}

int main() {
    int vertices = 5;
    vector<Edge> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    auto start_time = chrono::high_resolution_clock::now();
    bellmanFord(vertices, edges, 0);
    auto end_time = chrono::high_resolution_clock::now();
    
    chrono::duration<double> duration = end_time - start_time;
    cout << "Time taken: " << duration.count() << " seconds" << endl;

    return 0;
}

