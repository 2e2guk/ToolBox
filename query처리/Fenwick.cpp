// fenwick tree
// PURQ, RUPQ, RURQ 모두 지원
// 코드 자체는 1-based로 구현. 0-based 호출한다고 가정. 
// main 함수 사용 예시는 boj 10999
#include <bits/stdc++.h>
using namespace std;

// 점 업데이트, 구간 쿼리
template<typename T>    
struct fenwick_PURQ {  
    int n;  
    vector<T> tree;  
    fenwick_PURQ(int n) : n(n) { tree.resize(n + 1); }  
    T sum(int i) {  
        T ret = 0;  
        for (; i; i -= i & -i) ret += tree[i];  
        return ret;  
    }  
    void update(int i, T x) { for (i++; i <= n; i += i & -i) tree[i] += x; }  
    T query(int l, int r) { return l > r ? 0 : sum(r + 1) - sum(l); }  
};
// 구간 업데이트, 점 쿼리
template<typename T>  
struct fenwick_RUPQ {  
    fenwick_PURQ<T> f;  
    fenwick_RUPQ(int n) : f(fenwick_PURQ<T>(n + 1)) {}  
    void update(int l, int r, T x) { f.update(l, x), f.update(r + 1, -x); }  
    T query(int i) { return f.query(0, i); }  
};
// 구간 업데이트, 구간 쿼리
template<typename T>  
struct fenwick_RURQ {  
    int N;  
    fenwick_PURQ<T> A, B;  
    fenwick_RURQ(int N) : N(N), A(fenwick_PURQ<T>(N + 1)), B(fenwick_PURQ<T>(N + 1)) {}  
    
    void update(int L, int R, T d) {  
        A.update(L, d);  
        A.update(R + 1, -d);  
    
        B.update(L, (-L + 1) * d);  
        B.update(R + 1, R * d);  
    }  
    
    T query(int L, int R) {  
        T R_Value = A.query(0, R) * R + B.query(0, R);  
        T L_Value = 0;  
        if (L > 0) {  
            L_Value = A.query(0, L - 1) * (L - 1) + B.query(0, L - 1);  
        }  
        return R_Value - L_Value;  
    }  
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;  
    vector<ll> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    fenwick_RURQ<ll> fenw(n);  
    for (int i = 0; i < n; i++) fenw.update(i, i, a[i]);
    for (int i = 0; i < m + k; i++) {  
        ll x, y, z, u;  
        cin >> x;
        if (x == 1) {  
            int l, r; ll val; cin >> l >> r >> val; l--; r--;
            fenw.update(l, r, val);  
        } else {  
            int l, r; cin >> l >> r; l--; r--;
            cout << fenw.query(l, r) << "\n";  
        }  
    }  
    return 0;
}
