// Chinese Remainder Theorem(중국인의 나머지 정리)
// O(k log M) -> k는 합동식의 개수, m은 mod 중 최댓값
// main 함수 예시는 boj 12971 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mod(ll a, ll b){ return (a %= b) >= 0 ? a : a + b; }
tuple<ll,ll,ll> ext_gcd(ll a, ll b){
  if(b == 0) return {a, 1, 0};
  auto [g,x,y] = ext_gcd(b, a % b);
  return {g, y, x - a/b * y};
}
pair<ll,ll> crt(ll a1, ll m1, ll a2, ll m2){
  ll g = gcd(m1, m2), m = m1 / g * m2;
  if((a2 - a1) % g) return {-1, -1};
  ll md = m2/g, s = mod((a2-a1)/g, m2/g);
  ll t = mod(get<1>(ext_gcd(m1/g%md, m2/g)), md);
  return { a1 + s * t % md * m1, m };
}
// a = a_i (mod m_i)를 만족하는 {a, lcm(m_1, ... , m_k)} 반환
// a가 존재하지 않는 경우 {-1, -1} 반환
pair<ll,ll> crt(const vector<ll> &a, const vector<ll> &m){
  ll ra = a[0], rm = m[0];
  for(int i=1; i<m.size(); i++){
    auto [aa,mm] = crt(ra, rm, a[i], m[i]);
    if(mm == -1) return {-1, -1}; else tie(ra,rm) = tie(aa,mm);
  }
  return {ra, rm};
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    vector<ll> p(3, 0);
    vector<ll> x(3, 0);
    for(int i = 0; i < 3; i++) cin >> p[i];
    for(int i = 0; i < 3; i++) cin >> x[i];
    cout << crt(x, p).first;
    return 0;
}
