// boj 25365 Kingdom partition 
// maxflow
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX = numeric_limits<ll>::max();

template<typename FlowType>
class Dinic {
    struct Edge {
        int v, rev;
        FlowType flow, C;
    };
    int V;
    vector<int> level;
    vector<vector<Edge>> adj;

public:
    Dinic(int V) : V(V), adj(V), level(V) {}

    void addEdge(int u, int v, FlowType C) {
        Edge a{v, int(adj[v].size()), 0, C};
        Edge b{u, int(adj[u].size()), 0, 0};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }
    void clear() {
        for(int i = 0; i < V; i++) adj[i].clear();
        fill(level.begin(), level.end(), 0);
    }
    bool BFS(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (Edge &e : adj[u]) {
                if (level[e.v] < 0 && e.flow < e.C) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return level[t] >= 0;
    }
    FlowType DFS(int u, FlowType flow, int t, vector<int> &start) {
        if (u == t) return flow;

        for (; start[u] < adj[u].size(); start[u]++) {
            Edge &e = adj[u][start[u]];
            if (level[e.v] == level[u] + 1 && e.flow < e.C) {
                FlowType curr_flow = min(flow, e.C - e.flow);
                FlowType temp_flow = DFS(e.v, curr_flow, t, start);

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
        if (s == t) return -1;
        FlowType total = 0;
        while (BFS(s, t)) {
            vector<int> start(V);
            while (FlowType flow = DFS(s, numeric_limits<FlowType>::max(), t, start))
                total += flow;
        }
        return total;
    }
    tuple<FlowType, vector<int>, vector<int>, vector<pair<int, int>>> getMincut(int s, int t) {
        FlowType maxflow = Maxflow(s, t);
        vector<int> S, T;
        vector<pair<int, int>> saturated_edges;
        BFS(s, t);
        for(int i = 0; i < V; i++) (level[i] != -1 ? S : T).push_back(i);
        for(auto i : S) for(auto e : adj[i]) if(e.C != 0 && level[e.v] == -1) saturated_edges.emplace_back(i, e.v);
        return {maxflow, S, T, saturated_edges};
    }
};
int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n, m; cin >> n >> m;
    Dinic<ll> mf(2 * n + 2);
    int src = 2 * n;
    int sink = 2 * n + 1;
	int s, t; cin >> s >> t; s--; t--;
	mf.addEdge(src, 2 * s, MAX); 
    mf.addEdge(src, 2 * t + 1, MAX);

	mf.addEdge(2 * s + 1, sink, MAX); 
    mf.addEdge(2 * t, sink, MAX);
	for(int i = 0; i < m; i++) {
		int u, v, l; cin >> u >> v >> l; u--; v--;
		mf.addEdge(2 * u, 2 * v + 1, l);
        mf.addEdge(2 * v + 1, 2 * u, l);

		mf.addEdge(2 * u + 1, 2 * v, l);
		mf.addEdge(2 * v, 2 * u + 1, l);
	}
	cout << mf.Maxflow(src, sink) << "\n";
	auto [maxflow, S, T, saturated_edges] = mf.getMincut(src, sink);

    for(int i = 0; i < n; i++) {
        if(find(S.begin(), S.end(), 2 * i) != S.end() && find(T.begin(), T.end(), 2 * i + 1) != T.end())
            cout << "A";
        else if(find(T.begin(), T.end(), 2 * i) != T.end() && find(S.begin(), S.end(), 2 * i + 1) != S.end())
            cout << "B";
        else
            cout << "C";
    }
	return 0;
}
