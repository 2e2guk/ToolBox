// boj 2268 수들의 합 7
// fenwick tree
// PURQ, RUPQ, RURQ 모두 지원
// 코드 자체는 1-based로 구현. 0-based 호출한다고 가정. 
// main 함수 사용 예시는 boj 10999
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename ValueType, typename IndexType>
struct fenwick_PURQ {  
    IndexType n;  
    vector<ValueType> tree;  
    fenwick_PURQ(IndexType n) : n(n) { tree.resize(n + 1); }  

    ValueType sum(IndexType i) {  
        ValueType ret = 0;  
        for (; i; i -= i & -i) ret += tree[i];  
        return ret;  
    }  

    void update(IndexType i, ValueType x) { for (i++; i <= n; i += i & -i) tree[i] += x; }  

    ValueType query(IndexType l, IndexType r) { return l > r ? 0 : sum(r + 1) - sum(l); }  
};

template<typename ValueType, typename IndexType>
struct fenwick_RUPQ {  
    fenwick_PURQ<ValueType, IndexType> f;  
    fenwick_RUPQ(IndexType n) : f(fenwick_PURQ<ValueType, IndexType>(n + 1)) {}  

    void update(IndexType l, IndexType r, ValueType x) { f.update(l, x), f.update(r + 1, -x); }  

    ValueType query(IndexType i) { return f.query(0, i); }  
};

template<typename ValueType, typename IndexType>
struct fenwick_RURQ {  
    IndexType N;  
    fenwick_PURQ<ValueType, IndexType> A, B;  
    fenwick_RURQ(IndexType N) : N(N), A(fenwick_PURQ<ValueType, IndexType>(N + 1)), B(fenwick_PURQ<ValueType, IndexType>(N + 1)) {}  

    void update(IndexType L, IndexType R, ValueType d) {  
        A.update(L, d);  
        A.update(R + 1, -d);  

        B.update(L, (-L + 1) * d);  
        B.update(R + 1, R * d);  
    }  

    ValueType query(IndexType L, IndexType R) {  
        ValueType R_Value = A.query(0, R) * R + B.query(0, R);  
        ValueType L_Value = 0;  
        if (L > 0) {  
            L_Value = A.query(0, L - 1) * (L - 1) + B.query(0, L - 1);  
        }  
        return R_Value - L_Value;  
    }  
}; 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    fenwick_PURQ<ll, ll> fenw(n);  
    vector<ll> a(n, 0);
    for (int i = 0; i < n; i++) fenw.update(i, a[i]);
    for (int i = 0; i < m; i++) {  
        ll x; cin >> x;
        if (x == 1) {  
            ll idx, val; cin >> idx >> val;
            ll diff = val - a[idx - 1];
            a[idx - 1] = val;
            fenw.update(idx - 1, diff);  
        } else {  
            ll l, r; cin >> l >> r;
            if(l > r) swap(l, r);
            cout << fenw.query(l - 1, r - 1) << "\n";  
        }  
    }  
    return 0;
}
