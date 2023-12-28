// hungarian(kuhn-munkres) - 할당 문제 해결
// O(N^3)
//main 함수는 boj 14216
#include <bits/stdc++.h>
using namespace std;

template<typename CostType>
struct Hungarian {
    int n; 
    vector<vector<CostType>> mat;
    Hungarian(int n) : n(n), mat(n + 1, vector<CostType>(n + 1, numeric_limits<CostType>::max())) {}
    void addEdge(int u, int v, CostType cost){ mat[u][v] = min(mat[u][v], cost); }

    pair<CostType, vector<int>> run() {
        vector<CostType> u(n + 1), v(n + 1), m(n + 1);
        vector<int> p(n + 1), w(n + 1), c(n + 1);
        for(int i=1, a, b; i<=n; i++){
            p[0] = i; b = 0; fill(m.begin(), m.end(), numeric_limits<CostType>::max()); fill(c.begin(), c.end(), 0);
            do{
                int nxt; CostType delta = numeric_limits<CostType>::max(); c[b] = 1; a = p[b];
                for(int j = 1; j <= n; j++){
                    if(c[j]) continue;
                    CostType t = mat[a][j] - u[a] - v[j];
                    if(t < m[j]) m[j] = t, w[j] = b;
                    if(m[j] < delta) delta = m[j], nxt = j;
                }
                for(int j = 0; j <= n; j++){
                    if(c[j]) u[p[j]] += delta, v[j] -= delta; else m[j] -= delta;
                }
                b = nxt;
            }while(p[b] != 0);
            do{int nxt = w[b]; p[b] = p[nxt]; b = nxt;}while(b != 0);
        }
        vector<int> assign(n + 1); for(int i = 1; i <= n; i++) assign[p[i]] = i;
        return {-v[0], assign};
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    Hungarian<int> hungarian(N);

    // 입력으로 주어진 비용을 Hungarian 구조체에 추가
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            int cost; cin >> cost;
            hungarian.addEdge(i, j, cost);
        }
    }
    // Hungarian 알고리즘을 실행하여 결과를 받음
    auto result = hungarian.run();

    // 최소 비용 출력
    cout << result.first;
    return 0;
}
