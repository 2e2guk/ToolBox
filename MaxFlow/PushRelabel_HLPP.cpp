// push-relabel + HLPP opt
// O(VE + V^2sqrt(E)) -> O(V^3)(worst case)
// main 함수 사용 예시는 boj 11406
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename FlowType>
class HLPP {
public:
    struct Edge {
        int to, rev;
        FlowType flow, cap;
    };

    int n;
    vector<vector<Edge>> graph;
    vector<int> height, excess;

    HLPP(int n) : n(n), graph(n), height(n), excess(n) {}

    void addEdge(int from, int to, FlowType cap) {
        graph[from].push_back({to, int(graph[to].size()), 0, cap});
        graph[to].push_back({from, int(graph[from].size()) - 1, 0, 0});
    }

    void push(Edge &e, int u, int v) {
        FlowType d = min(excess[u], e.cap - e.flow);
        e.flow += d;
        graph[v][e.rev].flow -= d;
        excess[u] -= d;
        excess[v] += d;
    }

    void relabel(int u) {
        FlowType d = numeric_limits<FlowType>::max();
        for (auto& e : graph[u]) {
            if (e.cap - e.flow > 0)
                d = min(d, height[e.to]);
        }
        if (d < numeric_limits<FlowType>::max()) height[u] = d + 1;
    }

    vector<int> find_max_height_vertices(int s, int t) {
        vector<int> max_height;
        for (int i = 0; i < n; i++) {
            if (i != s && i != t && excess[i] > 0) {
                if (!max_height.empty() && height[i] > height[max_height[0]])
                    max_height.clear();
                if (max_height.empty() || height[i] == height[max_height[0]])
                    max_height.push_back(i);
            }
        }
        return max_height;
    }

    FlowType Maxflow(int s, int t) {
        height.assign(n, 0);
        height[s] = n;
        excess.assign(n, 0);
        excess[s] = numeric_limits<FlowType>::max();
        for (auto &e : graph[s]) {
            push(e, s, e.to);
        }

        vector<int> current;
        while (!(current = find_max_height_vertices(s, t)).empty()) {
            for (int i : current) {
                bool pushed = false;
                for (auto &e : graph[i]) {
                    if (excess[i] && e.cap - e.flow > 0 && height[i] == height[e.to] + 1) {
                        push(e, i, e.to);
                        pushed = true;
                        if (excess[i] == 0) break;
                    }
                }
                if (!pushed) {
                    relabel(i);
                    break;
                }
            }
        }

        FlowType max_flow = 0;
        for (auto &e : graph[s])
            max_flow += e.flow;
        return max_flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    HLPP<int> hlpp(N + M + 2);
    int s = 0, t = N + M + 1;
    for(int i = 1; i <= N; i++) {
        int a; cin >> a;
        hlpp.addEdge(s, i, a);
    }
    for(int i = 1; i <= M; i++) {
        int b; cin >> b;
        hlpp.addEdge(N + i, t, b);
    }
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            int c; cin >> c;
            hlpp.addEdge(j, N + i, c);
        }
    }
    cout << hlpp.Maxflow(s, t) << "\n";
    return 0;
}
