// merge-sort tree
// main 함수는 boj 13544 수열과 쿼리 3
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_ST = 1 << 18;
 
// 머지 소트 트리
template<typename ValueType>
struct MergesortTree {
    vector<ValueType> arr[MAX_ST];

    void construct() {
        for(int i = MAX_ST/2-1; i > 0; i--) {
            vector<ValueType> &c = arr[i], &l = arr[i*2], &r = arr[i*2+1];
            arr[i].resize(l.size()+r.size());
            for(int j = 0, p = 0, q = 0; j < c.size(); ++j) {
                if(q == r.size() || (p < l.size() && l[p] < r[q])) c[j] = l[p++];
                else c[j] = r[q++];
            }
        }
    }
 
    int greater(int s, int e, int k, int node = 1, int ns = 0, int ne = MAX_ST / 2) {
        if(ne <= s || e <= ns) return 0;
        if(s <= ns && ne <= e)
            return arr[node].end() - upper_bound(arr[node].begin(), arr[node].end(), k);
        int mid = (ns + ne) / 2;
        return greater(s, e, k, node * 2, ns, mid) + greater(s, e, k, node * 2 + 1, mid, ne);
    }
};
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int N, M, L = 0; 
    MergesortTree<ll> ST;

    cin >> N;
    for(int i = 0; i < N; i++) {
        ll val; cin >> val;
        ST.arr[MAX_ST / 2 + i].push_back(val);
    }

    ST.construct();

    cin >> M;
    for(int i = 0; i < M; i++) {
        ll s, e, k; cin >> s >> e >> k;
        cout << (L = ST.greater((s^L) - 1, e^L, k^L)) << "\n";
    }
    return 0;
}
