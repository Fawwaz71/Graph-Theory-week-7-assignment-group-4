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

example:


<img width="468" height="244" alt="image" src="https://github.com/user-attachments/assets/1e0c564b-e417-4e7d-9203-c6e480d9f9f2" />

<img width="545" height="153" alt="image" src="https://github.com/user-attachments/assets/da0ae045-63d2-455a-bc6f-732c6e363065" />




# The Knight Tour
```
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r, c;
} Pos;

int dr[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int isValid(int r, int c, int n, int m, int **visited) {
    return (r >= 0 && r < n && c >= 0 && c < m && visited[r][c] == 0);
}
```
## Hitung berapa banyak langkah valid yang bisa diambil dari posisi (r, c)
```
int countMoves(int r, int c, int n, int m, int **visited) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (isValid(nr, nc, n, m, visited))
            count++;
    }
    return count;
}
```
## Urutkan langkah-langkah berdasarkan jumlah langkah lanjutannya (heuristik Warnsdorff)

```
int nextMoves(int r, int c, int n, int m, int **visited, Pos moves[]) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (isValid(nr, nc, n, m, visited)) {
            moves[count].r = nr;
            moves[count].c = nc;
            count++;
        }
    }
```
## Sort berdasarkan jumlah kemungkinan langkah (ascending)

```    
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (countMoves(moves[i].r, moves[i].c, n, m, visited) >
                countMoves(moves[j].r, moves[j].c, n, m, visited)) {
                Pos temp = moves[i];
                moves[i] = moves[j];
                moves[j] = temp;
            }
        }
    }

    return count;
}

int solveKnightTour(int r, int c, int step, int total, int n, int m, int **visited, Pos *path) {
    path[step].r = r;
    path[step].c = c;
    visited[r][c] = 1;

    if (step + 1 == total)
        return 1;  // semua kotak dikunjungi

    Pos moves[8];
    int count = nextMoves(r, c, n, m, visited, moves);

    for (int i = 0; i < count; i++) {
        if (solveKnightTour(moves[i].r, moves[i].c, step + 1, total, n, m, visited, path))
            return 1;
    }

    visited[r][c] = 0; // backtrack
    return 0;
}
```
## main
```
int main() {
    int n, m;
    scanf("%d %d", &n, &m); // ukuran papan
    int sr, sc;
    scanf("%d %d", &sr, &sc); // posisi awal kuda
```
##  alokasi memori
    int **visited = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        visited[i] = calloc(m, sizeof(int));
    }

    Pos *path = malloc(n * m * sizeof(Pos));

    if (solveKnightTour(sr, sc, 0, n * m, n, m, visited, path)) {
        for (int i = 0; i < n * m; i++)
            printf("%d %d\n", path[i].r, path[i].c);
    } else {
        printf("No tour found\n");
    }

    for (int i = 0; i < n; i++)
        free(visited[i]);
    free(visited);
    free(path);

    return 0;
}



