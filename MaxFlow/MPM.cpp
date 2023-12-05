// MPM(Malhotra, Pramodh-Kumar and Maheshwari) maxflow algorithm
// O(V^3)
// main 함수는 boj 11406
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename FlowType>
struct MPM {
    struct FlowEdge {
        int v, u;
        FlowType cap, flow;
        FlowEdge(){}
        FlowEdge(int _v, int _u, FlowType _cap, FlowType _flow)
            : v(_v), u(_u), cap(_cap), flow(_flow){}
        FlowEdge(int _v, int _u, FlowType _cap)
            : v(_v), u(_u), cap(_cap), flow(0ll){}
    };
    const FlowType flow_inf = (FlowType)1e18;
    vector<FlowEdge> edges; vector<char> alive;
    vector<FlowType> pin, pout; vector<list<int>> in, out;
    vector<vector<int>> adj; vector<FlowType> ex;
    int n, m = 0; int s, t;
    vector<int> level; vector<int> q;
    int qh, qt;
    void resize(int _n) {
        n = _n;
        ex.resize(n); q.resize(n); pin.resize(n); pout.resize(n);
        adj.resize(n); level.resize(n); in.resize(n); out.resize(n);
    }
    MPM(){}
    MPM(int _n, int _s, int _t){ resize(_n); s = _s; t = _t; }
    void add_edge(int v, int u, FlowType cap){
        edges.push_back(FlowEdge(v, u, cap)); edges.push_back(FlowEdge(u, v, 0));
        adj[v].push_back(m); adj[u].push_back(m + 1);
        m += 2;
    }
    bool BFS() {
        while(qh < qt) {
            int v = q[qh++];
            for(int id : adj[v]) {
                if(edges[id].cap - edges[id].flow < 1)continue;
                if(level[edges[id].u] != -1)continue;
                level[edges[id].u] = level[v] + 1;
                q[qt++] = edges[id].u;
            }
        }
        return level[t] != -1;
    }
    FlowType pot(int v){ return min(pin[v], pout[v]); }
    void remove_node(int v) {
        for(int i : in[v]) {
            int u = edges[i].v;
            auto it = find(out[u].begin(), out[u].end(), i);
            out[u].erase(it);
            pout[u] -= edges[i].cap - edges[i].flow;
        }
        for(int i : out[v]) {
            int u = edges[i].u;
            auto it = find(in[u].begin(), in[u].end(), i);
            in[u].erase(it);
            pin[u] -= edges[i].cap - edges[i].flow;
        }
    }
    void push(int from, int to, FlowType f, bool forw){
        qh = qt = 0;
        ex.assign(n, 0); ex[from] = f; q[qt++] = from;
        while(qh < qt) {
            int v = q[qh++];
            if(v == to)
                break;
            FlowType must = ex[v];
            auto it = forw ? out[v].begin() : in[v].begin();
            while(true) {
                int u = forw ? edges[*it].u : edges[*it].v;
                FlowType pushed = min(must, edges[*it].cap - edges[*it].flow);
                if(pushed == 0)break;
                if(forw) {
                    pout[v] -= pushed;
                    pin[u] -= pushed;
                } else {
                    pin[v] -= pushed;
                    pout[u] -= pushed;
                }
                if(ex[u] == 0)
                    q[qt++] = u;
                ex[u] += pushed; edges[*it].flow += pushed; edges[(*it)^1].flow -= pushed;
                must -= pushed;
                if(edges[*it].cap - edges[*it].flow == 0) {
                    auto jt = it;
                    ++jt;
                    if(forw) {
                        in[u].erase(find(in[u].begin(), in[u].end(), *it));
                        out[v].erase(it);
                    } else {
                        out[u].erase(find(out[u].begin(), out[u].end(), *it));
                        in[v].erase(it);
                    }
                    it = jt;
                }
                else break;
                if(!must)break;
            }
        }
    }
    FlowType flow() {
        FlowType ans = 0;
        while(true){
            pin.assign(n, 0); pout.assign(n, 0);
            level.assign(n, -1); alive.assign(n, true);
            level[s] = 0;
            qh = 0; qt = 1;
            q[0] = s;
            if(!BFS())
                break;
            for(int i = 0; i < n; i++) {
                out[i].clear(); in[i].clear();
            }
            for(int i = 0; i < m; i++) {
                if(edges[i].cap - edges[i].flow == 0)
                    continue;
                int v = edges[i].v, u = edges[i].u;
                if(level[v] + 1 == level[u] && (level[u] < level[t] || u == t)){
                    in[u].push_back(i);
                    out[v].push_back(i);
                    pin[u] += edges[i].cap - edges[i].flow;
                    pout[v] += edges[i].cap - edges[i].flow;
                }
            }
            pin[s] = pout[t] = flow_inf;
            while(true) {
                int v = -1;
                for(int i = 0; i < n; i++) {
                    if(!alive[i])continue;
                    if(v == -1 || pot(i) < pot(v))
                        v = i;
                }
                if(v == -1)
                    break;
                if(pot(v) == 0) {
                    alive[v] = false;
                    remove_node(v);
                    continue;
                }
                FlowType f = pot(v);
                ans += f;
                push(v, s, f, false);
                push(v, t, f, true);
                alive[v] = false;
                remove_node(v);
            }
        }
        return ans;
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    int s = 0, t = N + M + 1;
    MPM<ll> g(N + M + 2, s, t);
    for(int i = 1; i <= N; i++) {
        int a; cin >> a;
        g.add_edge(s, i, a);
    }
    for(int i = 1; i <= M; i++) {
        int b; cin >> b;
        g.add_edge(N + i, t, b);
    }
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            int c; cin >> c;
            g.add_edge(j, N + i, c);
        }
    }
    cout << g.flow() << "\n";
}
