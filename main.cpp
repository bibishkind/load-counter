#include <bits/stdc++.h>

using namespace std;

void add_edge(vector<int> graph[],
              int src, int dest) {
    graph[src].push_back(dest);
    graph[dest].push_back(src);
}

void find_paths(vector<vector<int> > &paths,
                vector<int> &path,
                vector<int> parent[],
                int n, int u) {
    if (u == -1) {
        paths.push_back(path);
        return;
    }
    for (int par: parent[u]) {
        path.push_back(u);
        find_paths(paths, path, parent,
                   n, par);
        path.pop_back();
    }
}

void bfs(vector<int> graph[],
         vector<int> parent[],
         int n, int start) {
    vector<int> dist(n, INT_MAX);
    queue<int> q;
    q.push(start);
    parent[start] = {-1};
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: graph[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                parent[v].clear();
                parent[v].push_back(u);
            } else if (dist[v] == dist[u] + 1) {
                parent[v].push_back(u);
            }
        }
    }
}

auto find_path(vector<int> graph[],
               int n, int start, int end) {
    vector<vector<int> > paths;
    vector<int> path;
    vector<int> parent[n];
    bfs(graph, parent, n, start);
    find_paths(paths, path, parent, n, end);
    path = paths[0];
    reverse(paths.begin(), paths.end());
    return path;
}

int main() {
    int v;
    int e;
    cin >> v;
    cin >> e;
    vector<int> graph[v];
    for (int i = 0; i < e; i++) {
        int f;
        int t;
        cin >> f;
        cin >> t;
        add_edge(graph, f, t);
    }
    int n;
    cin >> n;
    vector<int> loads(v, 0);
    for (int i = 0; i < n; i++) {
        int f;
        int t;
        int load;
        cin >> f;
        cin >> t;
        cin >> load;
        auto path = find_path(graph, v, f, t);
        for (auto j: path) {
            loads[j] += load;
        }
    }
    for (int i = 0; i < v; i++) {
        cout << i << " " << loads[i] << endl;
    }
    return 0;
}
