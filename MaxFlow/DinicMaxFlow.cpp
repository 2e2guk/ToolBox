// Dinic's Maxflow algorithm
// O(V^2E) 
// main 함수 예시는 boj 11406
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename FlowType>
struct Dinic {
    struct Edge {
        int v, rev;
        FlowType flow, cap;
    };

    int V;
    vector<int> level;
    vector<vector<Edge>> adj;
    map<pair<int, int>, int> edgeIndexMap;

    Dinic(int V) : V(V), adj(V), level(V) {}

    void addEdge(int u, int v, FlowType cap) {
        edgeIndexMap[{u, v}] = adj[u].size();
        Edge forward = {v, (int)adj[v].size(), 0, cap};
        Edge reverse = {u, (int)adj[u].size(), 0, 0};
        adj[u].push_back(forward);
        adj[v].push_back(reverse);
    }

    bool BFS_level_graph(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (Edge &e : adj[u]) {
                if (level[e.v] < 0 && e.flow < e.cap) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return level[t] >= 0;
    }

    FlowType DFS_blocking_flow(int u, FlowType flow, int t, vector<int> &start) {
        if (u == t) return flow;

        for (; start[u] < adj[u].size(); start[u]++) {
            Edge &e = adj[u][start[u]];
            if (level[e.v] == level[u] + 1 && e.flow < e.cap) {
                FlowType curr_flow = min(flow, e.cap - e.flow);
                FlowType temp_flow = DFS_blocking_flow(e.v, curr_flow, t, start);

                if (temp_flow > 0) {
                    e.flow += temp_flow;
                    adj[e.v][e.rev].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
        return 0;
    }

    FlowType Maxflow(int s, int t) {
        FlowType total = 0;
        while (BFS_level_graph(s, t)) {
            vector<int> start(V);
            while (FlowType flow = DFS_blocking_flow(s, numeric_limits<FlowType>::max(), t, start)) {
                total += flow;
            }
        }
        return total;
    }

    tuple<FlowType, vector<int>, vector<int>, vector<pair<int, int>>> getMincut(int s, int t) {
        FlowType maxflow = Maxflow(s, t);
        vector<int> S, T;
        vector<pair<int, int>> saturated_edges;
        BFS_level_graph(s, t);
        for(int i = 0; i < V; i++) (level[i] != -1 ? S : T).push_back(i);
        for(auto i : S) for(auto e : adj[i]) if(e.cap != 0 && level[e.v] == -1) saturated_edges.emplace_back(i, e.v);
        return {maxflow, S, T, saturated_edges};
    }

    FlowType getFlow(int u, int v) {
        auto it = edgeIndexMap.find({u, v});
        if (it != edgeIndexMap.end()) {
            return adj[u][it->second].flow;
        }
        return -1;
    }

    void clear() {
        for(int i = 0; i < V; i++) adj[i].clear();
        fill(level.begin(), level.end(), 0);
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;

    Dinic<int> g(N + M + 2);
    int s = 0, t = N + M + 1;
    for(int i = 1; i <= N; i++) {
        int a; cin >> a;
        g.addEdge(s, i, a);
    }
    for(int i = 1; i <= M; i++) {
        int b; cin >> b;
        g.addEdge(N + i, t, b);
    }
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            int c; cin >> c;
            g.addEdge(j, N + i, c);
        }
    }
    cout << g.Maxflow(s, t) << "\n";
    cout << "Additional implementation" << "\n";
    // 최소 컷 계산
    auto [maxflow, S, T, saturated_edges] = g.getMincut(s, t);
    // 결과 출력
    cout << "Maxflow: " << maxflow << "\n";
    cout << "S: ";
    for (auto v : S) cout << v << " ";
    cout << "\nT: ";
    for (auto v : T) cout << v << " ";
    cout << "\nSaturated Edges: \n";
    for (auto &[u, v] : saturated_edges) cout << "(" << u << ", " << v << ") , flow : " << g.getFlow(u, v) << "\n";
    cout << "\n";
    return 0;
}
