// circulation
// 
// main 함수 사용 예시는 boj 20135
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
    Dinic(int V) : V(V), adj(V), level(V) {}

    void addEdge(int u, int v, FlowType cap) {
        Edge a{v, int(adj[v].size()), 0, cap};
        Edge b{u, int(adj[u].size()), 0, 0};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }
    void clear() {
        for(int i = 0; i < V; i++) adj[i].clear();
        fill(level.begin(), level.end(), 0);
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
        if (s == t) return -1;
        FlowType total = 0;
        while (BFS_level_graph(s, t)) {
            vector<int> start(V);
            while (FlowType flow = DFS_blocking_flow(s, numeric_limits<FlowType>::max(), t, start))
                total += flow;
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
};
template<typename FlowType>
struct MaxFlowEdgeDemands {
    Dinic<FlowType> dinic;
    vector<FlowType> demand;
    FlowType totalDemand;
    int nodeCount;

    MaxFlowEdgeDemands(int V) : dinic(V + 2), nodeCount(V), totalDemand(0), demand(V, 0) {}

    void addEdgeWithDemand(int u, int v, FlowType capacity, FlowType lowerBound) {
        dinic.addEdge(u, v, capacity - lowerBound);
        demand[u] += lowerBound; // supply node
        demand[v] -= lowerBound; // demand node
    }

    int src = nodeCount, sink = nodeCount + 1;

    bool isFeasible() {
        for (int i = 0; i < nodeCount; ++i) {
            if (demand[i] < 0) {
                dinic.addEdge(src, i, -demand[i]);
                totalDemand += demand[i];
            } else if (demand[i] > 0) {
                dinic.addEdge(i, sink, demand[i]);
            }
        }

        // 기존의 싱크에서 소스로 가는 무한대 용량의 간선 추가
        dinic.addEdge(sink, src, numeric_limits<FlowType>::max());

        FlowType flow = dinic.Maxflow(src, sink);
        return flow == totalDemand;
    }

    FlowType solve() {
        if (!isFeasible()) {
            return -1; // No feasible solution exists.
        }

        // 실제 소스와 싱크 간의 최대 유량 계산
        return dinic.Maxflow(src, sink);
    }
};
