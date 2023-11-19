// push-relabel naive implementation
// O(V^2E)
// main 함수 사용 예시는 boj 11406 
#include <bits/stdc++.h>
using namespace std;

template<typename FlowType, typename SizeType>
struct PushRelabel {
    constexpr static FlowType INF = numeric_limits<FlowType>::max();

    struct Edge {
        SizeType v, inv; 
        FlowType rem, cap;
    };

    SizeType n;
    queue<SizeType> Q;
    vector<vector<Edge>> G;
    vector<SizeType> h;
    vector<FlowType> ex;

    PushRelabel(SizeType sz) : n(sz), G(sz), ex(sz), h(sz) {}

    void addEdge(SizeType u, SizeType v, FlowType cap) {
        G[u].push_back({ v, (SizeType)G[v].size(), cap, cap });
        G[v].push_back({ u, (SizeType)G[u].size() - 1, 0, cap });
    }

    void Push(SizeType u, Edge& e) {
        FlowType t = min(ex[u], e.rem);
        if (!t) return;
        e.rem -= t; G[e.v][e.inv].rem += t;
        ex[u] -= t; ex[e.v] += t;
        if (ex[e.v] == t) Q.push(e.v);
    }

    void Relabel(SizeType u) {
        SizeType mn = INF;
        for (auto& e : G[u]) if (e.rem) mn = min(mn, h[e.v]);
        h[u] = mn + 1;
    }

    void Discharge(SizeType u) {
        while (ex[u]) {
            for (auto& e : G[u]) if (h[u] - 1 == h[e.v]) if (Push(u, e), !ex[u]) return;
            if (ex[u]) Relabel(u);
        }
    }

    FlowType Maxflow(SizeType s, SizeType t) {
        ex[s] = INF; h[s] = n;
        for (auto& e : G[s]) Push(s, e);
        while (Q.size()) {
            SizeType u = Q.front(); Q.pop();
            if (u != s && u != t) Discharge(u);
        }
        return ex[t];
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;

    PushRelabel<int, int> g(N + M + 2);
    int s = 0, t = N + M + 1;
    for (int i = 1; i <= N; i++) {
        int a; cin >> a;
        g.addEdge(s, i, a);
    }
    for (int i = 1; i <= M; i++) {
        int b; cin >> b;
        g.addEdge(N + i, t, b);
    }
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            int c; cin >> c;
            g.addEdge(j, N + i, c);
        }
    }
    cout << g.Maxflow(s, t);
    return 0;
}
