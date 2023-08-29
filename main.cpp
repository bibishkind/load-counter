#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

void addEdge(vector<int> graph[], int src, int dest) {
    graph[src].push_back(dest);
    graph[dest].push_back(src);
}

void findPaths(vector<vector<int>>& paths, vector<int>& path, vector<int> parent[], int n, int u) {
    if (u == -1) {
        paths.push_back(path);
        return;
    }
    for (int par : parent[u]) {
        path.push_back(u);
        findPaths(paths, path, parent, n, par);
        path.pop_back();
    }
}

void bfs(vector<int> graph[], vector<int> parent[], int n, int start) {
    vector<int> dist(n, numeric_limits<int>::max());
    queue<int> q;
    q.push(start);
    parent[start] = { -1 };
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                parent[v].clear();
                parent[v].push_back(u);
            }
            else if (dist[v] == dist[u] + 1) {
                parent[v].push_back(u);
            }
        }
    }
}

vector<int> findPath(vector<int> graph[], int n, int start, int end) {
    vector<vector<int>> paths;
    vector<int> path;
    vector<int> parent[n];
    bfs(graph, parent, n, start);
    findPaths(paths, path, parent, n, end);
    path = paths[0];
    reverse(paths.begin(), paths.end());
    return path;
}

int main() {
    int numVertices, numEdges, numLoads;
    cin >> numVertices >> numEdges;
    vector<int> graph[numVertices];
    for (int i = 0; i < numEdges; i++) {
        int from, to;
        cin >> from >> to;
        addEdge(graph, from, to);
    }
    cin >> numLoads;
    vector<int> loads(numVertices, 0);
    for (int i = 0; i < numLoads; i++) {
        int from, to, load;
        cin >> from >> to >> load;
        auto path = findPath(graph, numVertices, from, to);
        for (auto j : path) {
            loads[j] += load;
        }
    }
    for (int i = 0; i < numVertices; i++) {
        cout << i << " " << loads[i] << endl;
    }
    return 0;
}