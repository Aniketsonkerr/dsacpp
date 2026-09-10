#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Edge structure for Kruskal's algorithm
struct Edge {
    int u, v, weight;
};

// Simple Disjoint Set Union (DSU) for cycle detection in Kruskal's
class DisjointSet {
    vector<int> parent;
public:
    DisjointSet(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unionSets(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);

        if (rootI != rootJ) {
            parent[rootI] = rootJ;
            return true;
        }
        return false;
    }
};

// Helper function to sort edges by weight
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// --- PRIM'S ALGORITHM ---
void primMST(int V, vector<vector<int>>& graph, bool showOutput) {
    vector<int> key(V, 999999);
    vector<int> parent(V, -1);
    vector<bool> visited(V, false);

    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int minKey = 999999;
        int u = -1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && !visited[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    int totalWeight = 0;
    if (showOutput) {
        cout << "PRIM'S ALGORITHM" << endl;
        cout << "MST Edges:" << endl;
    }

    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            if (showOutput) {
                cout << (char)('A' + parent[i]) << " - " << (char)('A' + i) << " : " << graph[i][parent[i]] << endl;
            }
            totalWeight += graph[i][parent[i]];
        }
    }

    if (showOutput) {
        cout << "Total MST Weight = " << totalWeight << endl << endl;
    }
}

// --- KRUSKAL'S ALGORITHM ---
void kruskalMST(int V, vector<Edge>& edges, bool showOutput) {
    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSet ds(V);
    vector<Edge> result;
    int totalWeight = 0;

    for (size_t i = 0; i < edges.size(); i++) {
        if (ds.unionSets(edges[i].u, edges[i].v)) {
            result.push_back(edges[i]);
            totalWeight += edges[i].weight;
            if (result.size() == (size_t)(V - 1)) break;
        }
    }

    if (showOutput) {
        cout << "KRUSKAL'S ALGORITHM" << endl;
        cout << "MST Edges:" << endl;
        for (size_t i = 0; i < result.size(); i++) {
            cout << (char)('A' + result[i].u) << " - " << (char)('A' + result[i].v) << " : " << result[i].weight << endl;
        }
        cout << "Total MST Weight = " << totalWeight << endl << endl;
    }
}

int main() {
    int V = 5;
    vector<vector<int>> graph = {
        {0, 2, 4, 0, 0},
        {2, 0, 0, 3, 0},
        {4, 0, 0, 0, 1},
        {0, 3, 0, 0, 0},
        {0, 0, 1, 0, 0}
    };

    vector<Edge> edges = {
        {0, 1, 2}, // A - B : 2
        {0, 2, 4}, // A - C : 4
        {1, 3, 3}, // B - D : 3
        {2, 4, 1}  // C - E : 1
    };

    primMST(V, graph, true);
    kruskalMST(V, edges, true);

    return 0;
}