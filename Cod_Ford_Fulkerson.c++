#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int from, to, capacity, flow;
    Edge(int f, int t, int c) : from(f), to(t), capacity(c), flow(0) {}
};

vector<vector<Edge>> buildResidualGraph(const vector<Edge>& edges, int n) {
    vector<vector<Edge>> graph(n);
    for (const Edge& e : edges) {
        graph[e.from].push_back(e);
        graph[e.to].push_back(Edge(e.to, e.from, 0));
    }
    return graph;
}

int fordFulkerson(vector<vector<Edge>>& graph, int source, int sink) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    while (true) {
        fill(visited.begin(), visited.end(), false);
        fill(parent.begin(), parent.end(), -1);

        queue<int> q;
        q.push(source);
        visited[source] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const Edge& e : graph[u]) {
                if (!visited[e.to] && e.capacity > e.flow) {
                    q.push(e.to);
                    visited[e.to] = true;
                    parent[e.to] = u;
                }
            }
        }

        if (!visited[sink]) {
            break;
        }

        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            for (Edge& e : graph[u]) {
                if (e.to == v) {
                    pathFlow = min(pathFlow, e.capacity - e.flow);
                    break;
                }
            }
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            for (Edge& e : graph[u]) {
                if (e.to == v) {
                    e.flow += pathFlow;
                    for (Edge& reverseEdge : graph[v]) {
                        if (reverseEdge.to == u) {
                            reverseEdge.flow -= pathFlow;
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }

    int maxFlow = 0;
    for (const Edge& e : graph[source]) {
        maxFlow += e.flow;
    }
    return maxFlow;
}

int main() {
    int n = 6;
    vector<Edge> edges = {Edge(0, 1, 10), Edge(0, 2, 5), Edge(1, 2, 15),
                          Edge(1, 3, 10), Edge(2, 3, 10), Edge(2, 4, 10),
                          Edge(3, 4, 5), Edge(3, 5, 15), Edge(4, 5, 10)};
    vector<vector<Edge>> graph = buildResidualGraph(edges, n);

    int source = 0;
    int sink = 5;
    int maxFlow = fordFulkerson(graph, source, sink);

    cout << "Fluxo máximo: " << maxFlow << endl;

    return 0;
}
