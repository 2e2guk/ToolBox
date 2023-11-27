// 뤼카의 정리
// Lucas C(13);
// C.calc(5, 3) = 5C3 = 10
// C.calc(10, 2) = 10C2 % 13 = 45 % 13 = 6
// 주의: P는 소수
// P가 크고(약 10억) n,r이 작으면(1000만 이하)
// 생성자에서 fac, inv를 1000만까지만 구해도 됨
// main 함수 사용 예시는 boj 11402
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename ValueType>
struct Lucas{ // init : O(P), query : O(log P)
    const size_t P;
    vector<ValueType> fac, inv;
    ValueType Pow(ValueType a, ValueType b){
        ValueType res = 1;
        for(; b; b>>=1, a=a*a%P) if(b & 1) res = res * a % P;
        return res;
    }
    Lucas(size_t P) : P(P), fac(P), inv(P) {
        fac[0] = 1; for(int i=1; i<P; i++) fac[i] = fac[i-1] * i % P;
        inv[P-1] = Pow(fac[P-1], P-2); for(int i=P-2; ~i; i--) inv[i] = inv[i+1] * (i+1) % P;
    }
    ValueType small(ValueType n, ValueType r) const { return r <= n ? fac[n] * inv[r] % P * inv[n-r] % P : (ValueType)0; }
    ValueType calc(ll n, ll r) const {
        if(n < r || n < 0 || r < 0) return 0;
        if(!n || !r || n == r) return 1; else return small(n%P, r%P) * calc(n/P, r/P) % P;
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll n, k, m; cin >> n >> k >> m;
    Lucas<ll> lucas(m);
    cout << lucas.calc(n, k);
    return 0;
}
