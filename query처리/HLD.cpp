// HLD
// O(log^2 N), 
// update(v, w) -> 정점 v의 가중치에 w를 더함, query(s, e) -> s->e 경로의 모든 정점의 가중치의 합(변경가능) 출력
// "트리" 에서 이 작업을 수행. 
#include <bits/stdc++.h>
using namespace std;

vector<int> inp[101010]; //입력 / 양방향 그래프

template<typename ValueType>
struct Seg{
    ValueType tree[1 << 18];
    ValueType sz = 1 << 17;

    void update(int x, ValueType v){
        x |= sz; tree[x] += v;
        while(x >>= 1){
            tree[x] = tree[x << 1] + tree[x << 1 | 1];
        }
    }

    ValueType query(int l, int r){
        l |= sz, r |= sz;
        ValueType ret = 0;
        while(l <= r){
            if(l & 1) ret += tree[l++];
            if(~r & 1) ret += tree[r--];
            l >>= 1, r >>= 1;
        }
        return ret;
    }
};

template<typename ValueType>
struct HLD {
    ValueType sz[101010], dep[101010], par[101010], top[101010], in[101010], out[101010];
    vector<ValueType> g[101010];
    Seg<int> seg;

    ValueType chk[101010];
    void dfs(int v = 1) {
        chk[v] = 1;
        for(auto i : inp[v]) {
            if(chk[i]) continue;
            chk[i] = 1;
            g[v].push_back(i);
            dfs(i);
        }
    }

    void dfs1(int v = 1) {
        sz[v] = 1;
        for(auto &i : g[v]) {
            dep[i] = dep[v] + 1; par[i] = v;
            dfs1(i); sz[v] += sz[i];
            if(sz[i] > sz[g[v][0]]) swap(i, g[v][0]);
        }
    }

    ValueType pv;
    void dfs2(int v = 1) {
        in[v] = ++pv;
        for(auto i : g[v]) {
            top[i] = i == g[v][0] ? top[v] : i;
            dfs2(i);
        }
        out[v] = pv;
    }

    void update(int v, ValueType w) {
        seg.update(in[v], w);
    }

    ValueType query(int a, int b) {
        ValueType ret = 0;
        while(top[a] ^ top[b]) {
            if(dep[top[a]] < dep[top[b]]) swap(a, b);
            ValueType st = top[a];
            ret += seg.query(in[st], in[a]);
            a = par[st];
        }
        if(dep[a] > dep[b]) swap(a, b);
        ret += seg.query(in[a], in[b]);
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q; //정점 개수, 쿼리 개수
    HLD<int> hld;
    // 간선정보 입력
    for(int i = 1; i < n; i++) {
        int s, e; cin >> s >> e;
        inp[s].push_back(e);
        inp[e].push_back(s);
    }
    hld.dfs(); hld.dfs1(); hld.dfs2();
    while(q--) {
        //1 v w : update v w
        //2 s e : query s e
        int op, a, b; cin >> op >> a >> b;
        if(op == 1) hld.update(a, b);
        else cout << hld.query(a, b) << "\n";
    }
}
