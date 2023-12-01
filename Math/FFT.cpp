// Fast Fourier Transform(FFT, 고속 푸리에 변환)
// O(N log N)
// main 함수 사용예시는 boj 1067
#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1);
typedef complex<double> cpx;
typedef long long ll;
/*
input : f => Coefficient, w => principal n-th root of unity
output : f => f(x_0), f(x_1), f(x_2), ... , f(x_n-1)
T(N) = 2T(N/2) + O(N)
*/
void FFT(vector<cpx> &v, bool inv) {
    ll S = v.size(); // ll 타입으로 선언

    for(ll i=1, j=0; i<S; i++) {
        ll bit = S >> 1;
        while(j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if(i < j) swap(v[i], v[j]);
    }

    for(ll k=1; k<S; k<<=1) {
        double angle = inv ? PI/k : -PI/k;
        cpx dir(cos(angle), sin(angle));
        for(ll i=0; i<S; i+=(k<<1)) {
            cpx unit(1, 0);
            for(ll j=0; j<k; j++) {
                cpx a = v[i+j], b = v[i+j+k] * unit;
                v[i+j] = a + b;
                v[i+j+k] = a - b;
                unit *= dir;
            }
        }
    }

    if(inv) {
        for(ll i=0; i<S; i++) v[i] /= S;
    }
}
/*
input : a => A's Coefficient, b => B's Coefficient
output : A * B
*/
vector<cpx> mul(vector<cpx> &v, vector<cpx> &u) {
    ll S = 1;
    while(S < max(v.size(), u.size())) S <<= 1;
    S <<= 1; // 벡터의 길이를 조정하여 곱셈을 위한 충분한 길이를 확보

    v.resize(S); FFT(v, false);
    u.resize(S); FFT(u, false);

    vector<cpx> w(S);
    for(ll i=0; i<S; i++) w[i] = v[i] * u[i];

    FFT(w, true); // 역 FFT 수행
    return w;
}

int main() { 
  	ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int N; cin >> N;
    vector<cpx> v(N*2), u(N);

    for(int i=0; i<N; i++) {
        int x; cin >> x;
        v[i] = v[i+N] = cpx(x, 0);
    }
    for(int i=0; i<N; i++) {
        int x; cin >> x;
        u[N-1-i] = cpx(x, 0);
    }

    vector<cpx> w = mul(v, u);

    int ans = 0;
    for(int i=0; i<w.size(); i++) ans = max(ans, (int)round(w[i].real()));

    cout << ans << "\n";
}
