// DSU (Disjoint Set Union, Union-Find)
// + 경로압축 + union by rank
// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/A
#include <bits/stdc++.h>
using namespace std;

template <typename IndexType>
struct DSU {
    vector<IndexType> parent, rank;
    DSU(IndexType n) : parent(n), rank(n, 1) {
        for(IndexType i = 0; i < n; i++) parent[i] = i;
    }

    // 임의의 원소 u가 속한 root 번호 반환
    // 경로 압축
    IndexType find(IndexType u) {
        if(u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }

    // u가 속한 집합을, v가 속한 집합으로 병합
    // union by rank
    void merge(IndexType u, IndexType v) {
        u = find(u); v = find(v);
        if(u == v) return;
        if(rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if(rank[u] == rank[v]) ++rank[v];
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    DSU<int> dsu(n);
    string op; int x, y;
    while(m--) {
        cin >> op >> x >> y; x--; y--;
        if(op == "union") dsu.merge(x, y);
        else {
            if(dsu.find(x) == dsu.find(y)) cout << "YES" << "\n";
            else cout << "NO" << "\n";
        }
    }
    return 0;
}
