// boj 25297 Parity Constraint Maximum Flow
// circulation
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

    FlowType getFlow(int u, int v) {
        auto it = edgeIndexMap.find({u, v});
        if (it != edgeIndexMap.end()) {
            return adj[u][it->second].flow;
        }
        return (FlowType)0;
    }

    void clear() {
        for(int i = 0; i < V; i++) adj[i].clear();
        fill(level.begin(), level.end(), 0);
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M, s, t; cin >> N >> M >> s >> t;
    Dinic<ll> dinic(N + 2); 
    int ns = 0, nt = N + 1;
    vector<ll> u(M + 1, 0), v(M + 1, 0), c(M + 1, 0), p(M + 1, 0);
    vector<ll> demand(N + 1, 0);
    ll D = 0;
    for(int i = 1; i <= M; i++) {
        cin >> u[i] >> v[i] >> c[i] >> p[i];
        if(p[i] == 0) {
            dinic.addEdge(u[i], v[i], (c[i] % 2) == 0 ? c[i] : c[i] - 1);
        } else {
            dinic.addEdge(u[i], v[i], (c[i] - 1) % 2 == 0 ? c[i] - 1 : c[i] - 2);
            demand[u[i]]++;
            demand[v[i]]--;
        }
    }
    for(int i = 1; i <= N; i++) {
        if(demand[i] % 2 != 0) {
            if(i == s || i == t) continue;
            else {
                cout << -1;
                return 0;
            }
        }
    }
    for(int i = 1; i <= N; i++) {
        if(demand[i] > 0) {
            D += demand[i];
            dinic.addEdge(i, nt, demand[i]);
        } 
        if(demand[i] < 0) dinic.addEdge(ns, i, -demand[i]);
    }
    dinic.addEdge(t, s, numeric_limits<ll>::max());
    ll feasibleflow = dinic.Maxflow(ns, nt);
    if(feasibleflow != D) cout << -1;
    else {
        ll maxflow = dinic.Maxflow(s, t);
        cout << maxflow << "\n";
        for(int i = 1; i <= M; i++) {
            if(p[i] == 1) cout << dinic.getFlow(u[i], v[i]) + 1 << "\n";
            else cout << dinic.getFlow(u[i], v[i]) << "\n";
        }
    }
    return 0;
}
