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
            tree[x] = max(tree[x << 1], tree[x << 1 | 1]);
        }
    }

    ValueType query(int l, int r){
        l |= sz, r |= sz;
        ValueType ret = 0;
        while(l <= r){
            if(l & 1) ret = max(ret, tree[l++]);
            if(~r & 1) ret = max(ret, tree[r--]);
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
            ret = max(ret, seg.query(in[st], in[a]));
            a = par[st];
        }
        if(a == b) return ret;
        if(dep[a] > dep[b]) swap(a, b);
        ret = max(ret, seg.query(in[a]+1, in[b]));
        return ret;
    }
};

struct Edge {
    int u, v, w;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    HLD<int> hld;
    vector<Edge> edges(n); // 간선 정보를 저장할 벡터
    vector<int> val(n + 1, 0); // 노드의 현재 값을 저장하는 배열

    // 간선 입력 및 저장
    for(int i = 1; i < n; i++) {
        int s, e, w; cin >> s >> e >> w;
        inp[s].push_back(e);
        inp[e].push_back(s);
        edges[i] = {s, e, w};
    }

    // HLD 빌드
    hld.par[1] = 0;
    hld.dep[1] = 0;
    hld.top[1] = 0;
    hld.dfs();
    hld.dfs1();
    hld.dfs2();

    // 간선 가중치를 자식 노드에 할당
    for(int i = 1; i < n; i++) {
        int s = edges[i].u;
        int e = edges[i].v;
        int w = edges[i].w;
        // 더 깊은 노드를 자식 노드로 선택
        if(hld.dep[s] > hld.dep[e]) swap(s, e);
        val[e] = w; // 자식 노드의 현재 값을 저장
        hld.update(e, w); // 자식 노드에 가중치 할당
    }

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int op, x, y; cin >> op >> x >> y;
        if(op == 1) {
            // 간선 번호 x의 가중치를 y로 변경
            int idx = x; // 간선 번호는 1부터 시작
            int s = edges[idx].u;
            int e = edges[idx].v;
            if(hld.dep[s] > hld.dep[e]) swap(s, e);
            int diff = y - val[e]; // 이전 값과의 차이를 계산
            val[e] = y; // 새로운 값으로 갱신
            hld.update(e, diff); // 차이를 더해줌
        } else {
            cout << hld.query(x, y) << '\n';
        }
    }
    return 0;
}
