// LCA -> main 함수는 boj 11437(https://www.acmicpc.net/problem/11437)
#include <bits/stdc++.h>
using namespace std;

template<typename ValueType, typename IndexType>
struct LCA {
    int N;
    int MAXLN;
    vector<vector<int>> tree;
    vector<vector<int>> par;
    vector<int> depth;
    vector<ValueType> node_values;

    unordered_map<IndexType, int> idx_map;
    vector<IndexType> idx_reverse_map;

    int idx_counter;

    // 생성자
    LCA() : idx_counter(0) {
    }

    int get_idx(IndexType idx) {
        auto it = idx_map.find(idx);
        if(it != idx_map.end()) {
            return it->second;
        } else {
            int new_idx = idx_counter++;
            idx_map[idx] = new_idx;
            idx_reverse_map.push_back(idx);
            tree.emplace_back();
            depth.push_back(0);
            node_values.emplace_back();
            return new_idx;
        }
    }

    // LCA 구성 간선 추가.
    void add_edge(IndexType u_idx, IndexType v_idx) {
        int u = get_idx(u_idx);
        int v = get_idx(v_idx);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // 노드에 값 부여
    void set_node_value(IndexType idx, ValueType value) {
        int u = get_idx(idx);
        node_values[u] = value;
    }

    void dfs(int node, int parent) {
        for(int next : tree[node]) {
            if(next == parent) continue;
            depth[next] = depth[node] + 1;
            par[0][next] = node;
            dfs(next, node);
        }
    }

    // LCA 전처리 -> LCA 쿼리 날리기 전에 호출 필수
    void prepare_LCA(IndexType root_idx) {
        N = idx_counter;
        MAXLN = ceil(log2(N)) + 1;
        par.assign(MAXLN, vector<int>(N));
        int root = get_idx(root_idx);
        depth[root] = 0;
        par[0][root] = root;
        dfs(root, -1);
        for(int i = 1; i < MAXLN; i++) {
            for(int j = 0; j < N; j++) {
                par[i][j] = par[i - 1][par[i - 1][j]];
            }
        }
    }

    // LCA 구하기
    IndexType LCA_query(IndexType u_idx, IndexType v_idx) {
        int u = get_idx(u_idx);
        int v = get_idx(v_idx);

        if(depth[u] < depth[v]) swap(u, v);
        for(int i = MAXLN - 1; i >= 0; i--) {
            if(depth[u] - (1 << i) >= depth[v]) {
                u = par[i][u];
            }
        }
        if(u == v) return idx_reverse_map[u];
        for(int i = MAXLN - 1; i >= 0; i--) {
            if(par[i][u] != par[i][v]) {
                u = par[i][u];
                v = par[i][v];
            }
        }
        return idx_reverse_map[par[0][u]];
    }

    // 노드에 들어있는 값 참조
    ValueType get_node_value(IndexType idx) {
        int u = get_idx(idx);
        return node_values[u];
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    LCA<int, int> lca; 
    int n; cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        lca.add_edge(u, v);
    }
    lca.prepare_LCA(1);
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        cout << lca.LCA_query(u, v) << "\n";
    }

    return 0;
}
