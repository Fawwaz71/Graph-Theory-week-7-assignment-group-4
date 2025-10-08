# TSP Problem
```
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
    int id;
    int from;
    int to;
    int cost;
};

int main() {
    int n, e;
    cin >> n >> e;

    int inf = 1000000000;
    vector<edge> edges(e);
    vector<vector<int>> cost(n + 1, vector<int>(n + 1, inf));
    vector<vector<int>> edgeid(n + 1, vector<int>(n + 1, -1));

    for (int i = 0; i < e; i++) {
        cin >> edges[i].id >> edges[i].from >> edges[i].to >> edges[i].cost;
        int u = edges[i].from;
        int v = edges[i].to;
        int c = edges[i].cost;
        int id = edges[i].id;

        if (c < cost[u][v] || (c == cost[u][v] && (edgeid[u][v] == -1 || id < edgeid[u][v]))) {
            cost[u][v] = cost[v][u] = c;
            edgeid[u][v] = edgeid[v][u] = id;
        }
    }

    int start;
    cin >> start;

    vector<int> nodes;
    for (int i = 1; i <= n; i++) {
        if (i != start)
            nodes.push_back(i);
    }

    int bestcost = inf;
    vector<int> bestroute;

    do {
        int now = start;
        int totalcost = 0;
        vector<int> route;
        bool invalid = false;

        for (int next : nodes) {
            if (edgeid[now][next] == -1) { invalid = true; break; }
            totalcost += cost[now][next];
            route.push_back(edgeid[now][next]);
            now = next;
        }

        if (invalid || edgeid[now][start] == -1)
            continue;

        totalcost += cost[now][start];
        route.push_back(edgeid[now][start]);

        if (totalcost < bestcost || (totalcost == bestcost && route < bestroute)) {
            bestcost = totalcost;
            bestroute = route;
        }

    } while (next_permutation(nodes.begin(), nodes.end()));

    if (bestcost == inf) {
        cout << "cost: -1\nroute:\n";
        return 0;
    }

    cout << "cost: " << bestcost << "\n";
    cout << "route: ";
    for (size_t i = 0; i < bestroute.size(); i++) {
        cout << bestroute[i];
        if (i + 1 < bestroute.size()) cout << ", ";
    }
    cout << "\n";

    return 0;
}
```
## initialization
```
int inf = 1000000000;
vector<edge> edges(e);
vector<vector<int>> cost(n + 1, vector<int>(n + 1, inf));
vector<vector<int>> edgeid(n + 1, vector<int>(n + 1, -1));
```
Initializes constants and data structures, edges stores all edge, cost holds the cost between nodes initialized to infinity, and edgeid stores the corresponding edge IDs initialized to -1 (meaning no connection yet).

## Reading and Storing Edges
```
for (int i = 0; i < e; i++) {
    cin >> edges[i].id >> edges[i].from >> edges[i].to >> edges[i].cost;
    int u = edges[i].from;
    int v = edges[i].to;
    int c = edges[i].cost;
    int id = edges[i].id;

    if (c < cost[u][v] || (c == cost[u][v] && (edgeid[u][v] == -1 || id < edgeid[u][v]))) {
        cost[u][v] = cost[v][u] = c;
        edgeid[u][v] = edgeid[v][u] = id;
    }
}
```
This loop reads all edges and updates the cost and edge ID for each node pair, ensuring that only the cheapest edge is stored for every connection.

## Building Node List
```
vector<int> nodes;
for (int i = 1; i <= n; i++) {
    if (i != start)
        nodes.push_back(i);
}
```
Creates a list of all nodes except the starting node, which will be permuted to explore all possible visiting orders.

## Setting Initial Best Route
```
int bestcost = inf;
vector<int> bestroute;
```
Initializes variables to find the lowest route cost and its corresponding sequence.

## Loop
```
do {
    int now = start;
    int totalcost = 0;
    vector<int> route;
    bool invalid = false;

    for (int next : nodes) {
        if (edgeid[now][next] == -1) { invalid = true; break; }
        totalcost += cost[now][next];
        route.push_back(edgeid[now][next]);
        now = next;
    }

    if (invalid || edgeid[now][start] == -1)
        continue;

    totalcost += cost[now][start];
    route.push_back(edgeid[now][start]);

    if (totalcost < bestcost || (totalcost == bestcost && route < bestroute)) {
        bestcost = totalcost;
        bestroute = route;
    }

} while (next_permutation(nodes.begin(), nodes.end()));
```
This block generates all permutations of visiting orders for the nodes, calculates the total cost for each route , skips disconnected routes, and updates the best route if a cheaper one is found.
## not found
```
if (bestcost == inf) {
    cout << "cost: -1\nroute:\n";
    return 0;
}
```
Checks if no valid route was found; if so, it outputs -1 and exits.
## print
```
cout << "cost: " << bestcost << "\n";
cout << "route: ";
for (size_t i = 0; i < bestroute.size(); i++) {
    cout << bestroute[i];
    if (i + 1 < bestroute.size()) cout << ", ";
}
cout << "\n";
```
Displays the minimum total cost and the corresponding sequence of edge IDs that form the optimal TSP route.
