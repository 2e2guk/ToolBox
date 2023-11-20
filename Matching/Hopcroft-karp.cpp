// hopcroft-karp <- bipartite matching
// O(sqrt(V) * E)
// main 함수 예시는 boj 11376
#include <bits/stdc++.h>
using namespace std;

// 적정히 조정
const int MAXN = 2005, MAXM = 1005;

template <typename MatchType>
class HopcroftKarp {
    vector<int> gph[MAXN];
    int dis[MAXN], vis[MAXN];
    vector<MatchType> l, r;

    bool bfs(int n) {
        queue<int> que;
        bool ok = 0;
        memset(dis, 0, sizeof(dis));
        for(int i = 0; i < n; i++) {
            if(l[i] == -1 && !dis[i]) {
                que.push(i);
                dis[i] = 1;
            }
        }
        while(!que.empty()) {
            int x = que.front();
            que.pop();
            for(auto &i : gph[x]) {
                if(r[i] == -1) ok = 1;
                else if(!dis[r[i]]) {
                    dis[r[i]] = dis[x] + 1;
                    que.push(r[i]);
                }
            }
        }
        return ok;
    }

    bool dfs(int x) {
        if(vis[x]) return 0;
        vis[x] = 1;
        for(auto &i : gph[x]) {
            if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))) {
                l[x] = i;
                r[i] = x;
                return 1;
            }
        }
        return 0;
    }

public:
    HopcroftKarp() { l.resize(MAXN, -1); r.resize(MAXM, -1); }

    void clear() {
        for(int i = 0; i < MAXN; i++) gph[i].clear();
    }

    void addEdge(int l, int r) {
        gph[l].push_back(r);
    }
    // n에 들어가는 것은, 왼쪽 정점 집합 L의 크기이다. 
    MatchType match(int n) {
        MatchType ret = 0;
        while(bfs(n)) {
            memset(vis, 0, sizeof(vis));
            for(int i = 0; i < n; i++) if(l[i] == -1 && dfs(i)) ret++;
        }
        return ret;
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    HopcroftKarp<int> hk;
    for(int i = 0; i < N; i++) {
        int S; cin >> S;
        for(int j = 0; j < S; j++) {
            int k; cin >> k; k--;
            // 두 번의 노드에 모두 해당 일을 연결
            hk.addEdge(i, k);
            hk.addEdge(i + N, k);
        }
    }
    cout << hk.match(2 * N);
    return 0;
}
