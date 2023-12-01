// Fast Fourier Transform(FFT, 고속 푸리에 변환)
// O(N log N)
// main 함수 사용예시는 boj 1067
#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cpx;
typedef long long ll;
const double pi = acos(-1);

/*
input : f => Coefficient, w => principal n-th root of unity
output : f => f(x_0), f(x_1), f(x_2), ... , f(x_n-1)
T(N) = 2T(N/2) + O(N)
*/
void FFT(vector<cpx> &f, cpx w){
	int n = f.size();
	if(n == 1) return; //base case
	vector<cpx> even(n >> 1), odd(n >> 1);
	for(int i=0; i<n; i++){
		if(i & 1) odd[i >> 1] = f[i];
		else even[i >> 1] = f[i];
	}
	FFT(even, w*w); FFT(odd, w*w);
	cpx wp(1, 0);
	for(int i=0; i<n/2; i++){
		f[i] = even[i] + wp * odd[i];
		f[i+n/2] = even[i] - wp * odd[i];
		wp *= w;
	}
}

/*
input : a => A's Coefficient, b => B's Coefficient
output : A * B
*/
vector<cpx> mul(vector<cpx> a, vector<cpx> b){
	int n = 1;
	while(n <= a.size() || n <= b.size()) n <<= 1;
	n <<= 1;
	a.resize(n); b.resize(n); vector<cpx> c(n);
	cpx w(cos(2*pi/n), sin(2*pi/n));
	FFT(a, w); FFT(b, w);
	for(int i=0; i<n; i++) c[i] = a[i] * b[i];
	FFT(c, cpx(1, 0) / w);
	for(int i=0; i<n; i++){
		c[i] /= cpx(n, 0);
		c[i] = cpx(round(c[i].real()), round(c[i].imag())); //result is integer
	}
	return c;
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int n; cin >> n;
	vector<int> A(2 * n), B(n);
	for(int i = 0; i < n; i++) cin >> A[i];
	for(int i = n - 1; i >= 0; i--) cin >> B[i];
	for(int i = 0; i < n; i++) A[i + n] = A[i];

	vector<cpx> a, b;
	for(auto i : A) a.push_back(cpx(i, 0));
	for(auto i : B) b.push_back(cpx(i, 0));

	vector<cpx> c = mul(a, b);

	ll ans = 0;
	for(int i = 0; i < c.size(); i++){
		ans = max<ll>(ans, round(c[i].real()));
	}
	cout << ans;
    return 0;
}
