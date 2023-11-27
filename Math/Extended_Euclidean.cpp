// (확장)유클리드 호제법
// gcd(A, B) ->  O(max(logA, logB)) -> 확장 유클리드 호제법도 이거 따라감
// main 함수는 boj 14565
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll x, ll y) { return __gcd(x, y); }
ll lcm(ll x, ll y) { return x / gcd(x, y) * y; }
ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) { // ax + by = gcd(a, b)
  ll g = a; x = 1, y = 0;
  if (b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
  return g;
}
ll inv(ll a, ll m){ //return x when ax mod m = 1, fail -> -1
    ll x, y;
    ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll mod, a; cin >> mod >> a;
    cout << mod - a << " " << inv(a, mod);
    return 0;
}
