// Dinic's Maxflow algorithm
// O(V^2E) <- G=(V, E)
#include <bits/stdc++.h>
using namespace std;

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

    FlowType DinicMaxflow(int s, int t) {
        if (s == t) return -1;

        FlowType total = 0;
        while (BFS(s, t)) {
            vector<int> start(V);
            while (FlowType flow = DFS(s, numeric_limits<FlowType>::max(), t, start))
                total += flow;
        }
        return total;
    }
};
