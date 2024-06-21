#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int fordFulkerson(vector<vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    vector<int> parent(n);
    int maxFlow = 0;

    while (true) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < n; ++v) {
                if (!visited[v] && graph[u][v] > 0) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        if (!visited[sink]) {
            break;
        }

        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, graph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            graph[u][v] -= pathFlow;
            graph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    int source, sink;
    cin >> source >> sink;

    int maxFlow = fordFulkerson(graph, source, sink);
    cout << "Fluxo máximo: " << maxFlow << endl;

    return 0;
}
