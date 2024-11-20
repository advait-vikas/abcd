#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

bool bfs(vector<vector<int>>& residualGraph, int s, int t, vector<int>& parent) {
    int V = residualGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                visited[v] = true;
                parent[v] = u;
            }
        }
    }
    return false;
}

int edmondsKarp(vector<vector<int>>& graph, int s, int t) {
    int V = graph.size();
    vector<vector<int>> residualGraph = graph;
    vector<int> parent(V);
    int maxFlow = 0;

    while (bfs(residualGraph, s, t, parent)) {
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main() {
    vector<vector<int>> graph = {
        {0, 3, 7, 0, 0, 0},
        {0, 0, 0, 3, 4, 0},
        {0, 5, 0, 0, 3, 0},
        {0, 0, 0, 0, 3, 2},
        {0, 0, 0, 0, 0, 6},
        {0, 0, 0, 0, 0, 0}};
    cout << "Maximum Flow: " << edmondsKarp(graph, 0, 5) << endl;
    return 0;
}
