#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
    int name;
    int from;
    int to;
    int cost;
};

int main() {
    int n, e, start;
    cin >> n >> e;

    int inf = 1000000001;
    vector<edge> edges(e);
    vector<vector<int>> cost(n + 1, vector<int>(n + 1, inf));
    vector<vector<int>> edge_name(n + 1, vector<int>(n + 1, -1));

    for (int i = 0; i < e; i++) {
        cin >> edges[i].name >> edges[i].from >> edges[i].to >> edges[i].cost;
        int u = edges[i].from;
        int v = edges[i].to;
        int c = edges[i].cost;
        int name = edges[i].name;

        if (c < cost[u][v] || (c == cost[u][v] && (edge_name[u][v] == -1 || name < edge_name[u][v]))) {
            cost[u][v] = cost[v][u] = c;
            edge_name[u][v] = edge_name[v][u] = name;
        }
    }
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

        for (int next:nodes) {
            totalcost += cost[now][next];
            route.push_back(edge_name[now][next]);
            now = next;
        }

        totalcost += cost[now][start];
        route.push_back(edge_name[now][start]);

        if (totalcost < bestcost || (totalcost == bestcost && route < bestroute)) {
            bestcost = totalcost;
            bestroute = route;
        }

    } while (next_permutation(nodes.begin(), nodes.end()));

    cout << "cost:" << bestcost << "\n";
    cout << "route:";
    for (size_t i = 0; i < bestroute.size(); i++) {
        cout << bestroute[i];
        if (i + 1 < bestroute.size()) cout << ",";
    }
    return 0;
}
