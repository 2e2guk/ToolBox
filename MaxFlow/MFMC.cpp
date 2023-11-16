// MCMF
// main함수 예시는 boj 15504
#include <bits/stdc++.h>
using namespace std;

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
                if(e.capacity > 0 && dist[u] + e.cost < dist[e.to]) {
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
    int N;
    cin >> N;
    vector<int> A(N + 1, 0), H(N + 1, 0), L(N + 1, 0);
    MCMF<int, int> mcmf(2 * N + 2);

    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) cin >> H[i];
    for(int i = 1; i <= N; i++) cin >> L[i];
    
    int src = 0, sink = 2 * N + 1;
    int max_A = *max_element(A.begin() + 1, A.end());

    for(int i = 1; i <= N; i++) {
        if(A[i] == max_A) {
            mcmf.addEdge(src, i, L[i], H[i]);
            mcmf.addEdge(i + N, sink, 0, H[i]);
        } else {
            mcmf.addEdge(src, i, L[i] - 1, H[i]);
            mcmf.addEdge(i + N, sink, 1, H[i]);
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(A[i] > A[j]) {
                int cost = A[i] ^ A[j];
                mcmf.addEdge(i, j + N, 1, -cost);
            }
        }
    }

    auto ans = mcmf.getMCMF(src, sink);
    cout << -ans.second << "\n";

    return 0;
}

