// boj 16833 Enlarge Circles
// MCMF
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-3;

template<typename FlowType, typename CostType>
class MCMF {
    struct Edge {
        int to;
        FlowType capacity;
        CostType cost;
        int rev;
    };

    int V;
    vector<vector<Edge>> adj;
    vector<CostType> dist;
    vector<int> previous, edgeIndex;

public:
    MCMF(int V) : V(V), adj(V) {}

    void addEdge(int from, int to, FlowType cap, CostType cost) {
        adj[from].push_back({to, cap, cost, (int)adj[to].size()});
        adj[to].push_back({from, 0, -cost, (int)adj[from].size() - 1});
    }

    bool SPFA(int src, int sink) {
        dist.assign(V, numeric_limits<CostType>::max());
        previous.assign(V, -1);
        edgeIndex.assign(V, -1);
        vector<bool> inQueue(V, false);

        queue<int> Q;
        dist[src] = 0;
        Q.push(src);
        inQueue[src] = true;

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inQueue[u] = false;

            for(int i = 0; i < adj[u].size(); ++i) {
                Edge &e = adj[u][i];
                if(e.capacity > 0 && dist[u] + e.cost + eps < dist[e.to]) {
                    dist[e.to] = dist[u] + e.cost;
                    previous[e.to] = u;
                    edgeIndex[e.to] = i;

                    if(!inQueue[e.to]) {
                        Q.push(e.to);
                        inQueue[e.to] = true;
                    }
                }
            }
        }
        return previous[sink] != -1;
    }
    pair<FlowType, CostType> getMCMF(int src, int sink) {
        FlowType maxFlow = 0;
        CostType minCost = 0;

        while (SPFA(src, sink)) {
            FlowType flow = numeric_limits<FlowType>::max();
            for(int v = sink; v != src; v = previous[v]) {
                int u = previous[v];
                flow = min(flow, adj[u][edgeIndex[v]].capacity);
            }
            for(int v = sink; v != src; v = previous[v]) {
                int u = previous[v];
                Edge &e = adj[u][edgeIndex[v]];
                e.capacity -= flow;
                adj[v][e.rev].capacity += flow;
                minCost += flow * e.cost;
            }
            maxFlow += flow;
        }
        return {maxFlow, minCost};
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); 
    int n; cin >> n;
    MCMF<int, double> mcmf(2 * n + 2);
    int src = 0, sink = 2 * n + 1;
    complex<double> a[n];
	for(int i = 0; i < n; i++){
		int x, y; cin >> x >> y;
		a[i] = complex<double>(x, y);
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i != j) mcmf.addEdge(i + 1, j + n + 1, 1, abs(a[i] - a[j]));
			else mcmf.addEdge(i + 1, j + n + 1, 1, numeric_limits<double>::max());
		}
		mcmf.addEdge(src, i + 1, 1, 0);
		mcmf.addEdge(i + n + 1, sink, 1, 0);
	}
    cout << fixed << setprecision(10);
    cout << mcmf.getMCMF(src, sink).second * acos(-1);
	return 0;
}
