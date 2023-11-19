// push relabel + FIFO
// O(V^3)
// main함수 사용 예시는 boj 11406 
#include <bits/stdc++.h>
using namespace std;

template<typename FlowType> 
struct Edge {
    int u, v, r; FlowType c, f;
    Edge() = default;
    Edge(int u, int v, FlowType c, int r) : u(u), v(v), r(r), c(c), f(0) {}
};
template<typename FlowType, size_t _Sz> 
struct PushRelabel {
    using edge_t = Edge<FlowType>;
    int n, b, dist[_Sz], count[_Sz+1];
    FlowType excess[_Sz]; bool active[_Sz];
    vector<edge_t> g[_Sz]; vector<int> bucket[_Sz];
    void clear(){ for(int i=0; i<_Sz; i++) g[i].clear(); }
    void addEdge(int s, int e, FlowType x){
        g[s].emplace_back(s, e, x, (int)g[e].size());
        if(s == e) g[s].back().r++;
        g[e].emplace_back(e, s, 0, (int)g[s].size()-1);
    }
    void enqueue(int v) {
        if(!active[v] && excess[v] > 0 && dist[v] < n){
        active[v] = true; bucket[dist[v]].push_back(v); b = max(b, dist[v]);
        }
    }
    void push(edge_t &e) {
        FlowType fl = min(excess[e.u], e.c - e.f);
        if(dist[e.u] == dist[e.v] + 1 && fl > FlowType(0)){
            e.f += fl; g[e.v][e.r].f -= fl; excess[e.u] -= fl; excess[e.v] += fl; enqueue(e.v);
        }
    }
    void gap(int k) {
        for(int i=0; i<n; i++){
            if(dist[i] >= k) count[dist[i]]--, dist[i] = max(dist[i], n), count[dist[i]]++; 
            enqueue(i);
        }
    }
    void relabel(int v) {
        count[dist[v]]--; 
        dist[v] = n;
        for(const auto &e : g[v]) if(e.c - e.f > 0) dist[v] = min(dist[v], dist[e.v] + 1);
        count[dist[v]]++; 
        enqueue(v);
    }
    void discharge(int v) {
        for(auto &e : g[v]) if(excess[v] > 0) push(e); else break;
        if(excess[v] > 0) if(count[dist[v]] == 1) gap(dist[v]); else relabel(v);
    }
    FlowType Maxflow(int _n, int s, int t) {
        memset(dist, 0, sizeof dist); memset(excess, 0, sizeof excess);
        memset(count, 0, sizeof count); memset(active, 0, sizeof active);
        n = _n; b = 0;
        for(auto &e : g[s]) excess[s] += e.c;
        count[s] = n; enqueue(s); active[t] = true;
        while(b >= 0){
        if(bucket[b].empty()) b--;
        else{
            int v = bucket[b].back(); bucket[b].pop_back();
            active[v] = false; discharge(v);
        }
        }
        return excess[t];
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    PushRelabel<int, 202> g; // 202는, network flow를 구성할 때 할당할 최대 size이다. 
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
    cout << g.Maxflow(N + M + 2, s, t); // 맨 앞에, 202중에서, 실제로 사용할 정점이 몇개인지를 입력으로 준다.
    return 0;
}

