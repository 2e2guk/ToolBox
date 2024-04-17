// CERC 2023 C Cakes
// boj 30947
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
    int G, C, T; cin >> G >> C >> T;

    Dinic<ll> g(C + T + 2);
    int s = 0, t = C + T + 1;
    vector<ll> cakeprice(C, 0);
    vector<ll> ingredientprice(G, 0);
    vector<ll> toolprice(T, 0);
    vector<vector<ll>> amount(C, vector<ll>(G, 0));
    for(int i = 0; i < C; i++) cin >> cakeprice[i];
    for(int i = 0; i < G; i++) cin >> ingredientprice[i];
    for(int i = 0; i < T; i++) cin >> toolprice[i];
    for(int i = 0; i < C; i++) {
        for(int j = 0; j < G; j++) {
            cin >> amount[i][j];
        }
    }
    // 소스 - 케잌 연결
    ll total = 0;
    for(int i = 0; i < C; i++) {
        ll cost = 0;
        for(int j = 0; j < G; j++) {
            cost += amount[i][j] * ingredientprice[j];
        }
        // 음수의 손실을 flow network에 포함시키는 것은, 정확한 결과를 구할 수 없게 만든다.
        if(cost > cakeprice[i]) continue;
        g.addEdge(s, i + 1, cakeprice[i] - cost);
        total += cakeprice[i] - cost;
    }
    // 도구 - 싱크 연결
    for(int i = 0; i < T; i++) g.addEdge(i + C + 1, t, toolprice[i]);
    // 케잌 - 도구 연결
    for(int i = 0; i < C; i++) {
        int num; cin >> num;
        for(int j = 0; j < num; j++) {
            int toolnum; cin >> toolnum;
            g.addEdge(i + 1, toolnum + C, numeric_limits<ll>::max());
        }
    }
    cout << total - g.Maxflow(s, t);
    return 0;
}
