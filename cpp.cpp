#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge {
    int u, v, cost;
};

int n, e, start;
vector<vector<int>> dist;       // shortest path matrix
vector<vector<int>> adjMatrix; // adjacency cost matrix
vector<vector<int>> adjList;   // adjacency list for Euler tour
vector<Edge> edges;

void floydWarshall() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

// Hierholzer’s algorithm to find Eulerian circuit
void eulerianCircuit(int u, vector<int>& path) {
    for (int v = 0; v < n; v++) {
        while (adjMatrix[u][v] > 0) {
            adjMatrix[u][v]--;
            adjMatrix[v][u]--;
            eulerianCircuit(v, path);
        }
    }
    path.push_back(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> e;

    adjMatrix.assign(n, vector<int>(n, 0));
    dist.assign(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    int totalCost = 0;
    for (int i = 0; i < e; i++) {
        int u, v, name, cost;
        cin >> u >> v >> name >> cost;
        edges.push_back({u, v, cost});
        adjMatrix[u][v]++;
        adjMatrix[v][u]++;
        dist[u][v] = min(dist[u][v], cost);
        dist[v][u] = min(dist[v][u], cost);
        totalCost += cost;
    }

    cin >> start;

    // Floyd-Warshall for all-pairs shortest paths
    floydWarshall();

    // Find odd degree vertices
    vector<int> degree(n, 0);
    for (auto &ed : edges) {
        degree[ed.u]++;
        degree[ed.v]++;
    }
    vector<int> oddVertices;
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 == 1) oddVertices.push_back(i);
    }

    int addCost = 0;
    if (!oddVertices.empty()) {
        // Brute force min matching (since n is small in test cases)
        int m = oddVertices.size();
        vector<int> perm(m);
        iota(perm.begin(), perm.end(), 0);

        int best = INF;
        do {
            int cur = 0;
            for (int i = 0; i < m; i += 2) {
                int a = oddVertices[perm[i]];
                int b = oddVertices[perm[i+1]];
                cur += dist[a][b];
            }
            best = min(best, cur);
        } while (next_permutation(perm.begin(), perm.end()));
        addCost = best;
    }

    int finalCost = totalCost + addCost;

    // Eulerian circuit reconstruction
    vector<int> path;
    eulerianCircuit(start, path);
    reverse(path.begin(), path.end());

    cout << "Cost: " << finalCost << "\n";
    cout << "Route: ";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i];
        if (i + 1 < (int)path.size()) cout << ", ";
    }
    cout << "\n";

    return 0;
}