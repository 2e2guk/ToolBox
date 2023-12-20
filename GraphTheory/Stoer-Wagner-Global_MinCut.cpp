// 음 아닌 가중치가 부여된, undirected graph에서, global min cut을 구해냄
// main 함수 사용 예시는 boj 14060 Paths in Multigraph
// Stoer-Wagner algorithm
// O(V^3), 0-based index. addEdge 사용시 주의
#include <bits/stdc++.h>
using namespace std;

template<typename CostType>
struct StoerWagner {
    int n;
    vector<vector<CostType>> graph;

    StoerWagner(int n) : n(n), graph(vector<vector<CostType>>(n, vector<CostType>(n, 0))) {}

    void addEdge(int u, int v, CostType w) {
        if (u == v) return;
        graph[u][v] += w;
        graph[v][u] += w;
    }

    pair<CostType, pair<int, int>> stMinCut(vector<int> &active) {
        vector<CostType> key(n);
        vector<int> v(n);
        int s = -1, t = -1;
        for (int i = 0; i < active.size(); i++) {
            CostType maxv = -1;
            int cur = -1;
            for (auto j : active) {
                if (v[j] == 0 && maxv < key[j]) {
                    maxv = key[j];
                    cur = j;
                }
            }
            t = s; s = cur;
            v[cur] = 1;
            for (auto j : active) key[j] += graph[cur][j];
        }
        return make_pair(key[s], make_pair(s, t));
    }

    vector<int> cut;

    CostType globalminCut() {
        CostType res = numeric_limits<CostType>::max();
        vector<vector<int>> grps;
        vector<int> active;
        cut.resize(n);
        for (int i = 0; i < n; i++) grps.emplace_back(1, i);
        for (int i = 0; i < n; i++) active.push_back(i);
        while (active.size() >= 2) {
            auto stcut = stMinCut(active);
            if (stcut.first < res) {
                res = stcut.first;
                fill(cut.begin(), cut.end(), 0);
                for (auto v : grps[stcut.second.first]) cut[v] = 1;
            }

            int s = stcut.second.first, t = stcut.second.second;
            if (grps[s].size() < grps[t].size()) swap(s, t);

            active.erase(find(active.begin(), active.end(), t));
            grps[s].insert(grps[s].end(), grps[t].begin(), grps[t].end());
            for (int i = 0; i < n; i++) { graph[i][s] += graph[i][t]; graph[i][t] = 0; }
            for (int i = 0; i < n; i++) { graph[s][i] += graph[t][i]; graph[t][i] = 0; }
            graph[s][s] = 0;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    StoerWagner<int> mc(N);
    for(int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        mc.addEdge(u, v, 1);
    }
    cout << mc.globalminCut() << "\n";
    return 0;
}
