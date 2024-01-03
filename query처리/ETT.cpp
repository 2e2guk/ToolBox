// ETT(Euler-Tour-Technique)
// main 함수 사용 예시는 boj 2820
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
int n, m;
vi a, par, in, out;
vvi edges;

int dfsn = 0;
template<typename ValueType>  
struct fenwick {  
    int n;  
    vector<ValueType> tree;  
    fenwick(int n) : n(n) { tree.resize(n + 1); }  
    ValueType sum(int i) {  
        ValueType ret = 0;  
        for (; i; i -= i & -i) ret += tree[i];  
        return ret;  
    }  
    void update(int i, ValueType x) { for (i++; i <= n; i += i & -i) tree[i] += x; }  
    ValueType query(int l, int r) { return l > r ? 0 : sum(r + 1) - sum(l); }  
};
template<typename ValueType> 
struct fenwick_point {  
    fenwick<ValueType> f;  
    fenwick_point(int n) : f(fenwick<ValueType>(n + 1)) {}  
    void update(int l, int r, ValueType x) { f.update(l, x), f.update(r + 1, -x); }  
    ValueType query(int i) { return f.query(0, i); }  
};

void dfs(int i) {
   in[i] = dfsn++;
   for (int child: edges[i]) {
      dfs(child);
   }
   out[i] = dfsn - 1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    a.resize(n); edges.resize(n);
    in.resize(n); out.resize(n);

    for (int i = 0; i < n; i++) {
        int x, p;
        cin >> x;
        if (i) cin >> p;
        a[i] = x;
        if (i)
            edges[p - 1].push_back(i);
    }

    dfs(0);
    fenwick_point<int> fw(n);
    for (int i = 0; i < n; i++) {
        fw.update(in[i], in[i], a[i]);
    }

    for (int i = 0; i < m; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "p") {
            int k, x;
            cin >> k >> x, k--;
            // 자기 자신은 제외하고 업데이트 해야 한다. 
            fw.update(in[k] + 1, out[k], x);
        } else {
            int k;
            cin >> k, k--;
            cout << fw.query(in[k]) << "\n";
        }
    }
    return 0;
}
