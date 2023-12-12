// 문자열 패턴 매칭 알고리즘
// Rabin-Karp algorithm(라빈-카프 알고리즘)
// Rolling- Hash 기법
#include <iostream>

using namespace std;

const int BASE = 401, MOD = 1e9 + 7, MAX = 1e6 + 6;
int HASH, len, HASH2, POWER[MAX];

void solve() {
   	POWER[0] = 1;
   	for (int i = 1; i < MAX; i++) POWER[i] = md(MOD, POWER[i - 1] * BASE);
   	string s, t;
   	getline(cin, s);
   	getline(cin, t);
   	len = sz(t);
   	if (sz(s) < len) {
    	cout << 0;
      	return;
   	}
   	for (int i = len - 1; i >= 0; i--) {
      	HASH = md(MOD, HASH + t[i] * POWER[len - 1 - i]);
      	HASH2 = md(MOD, HASH2 + s[i] * POWER[len - 1 - i]);
   	}
   	vi ans;
   	if (HASH == HASH2) ans.pb(0);
   	for (int i = 1; i + len - 1 < sz(s); i++) {
      	HASH2 = md(MOD, md(MOD, HASH2 - s[i - 1] * POWER[len - 1]) * BASE + s[i + len - 1]);
      	if (HASH == HASH2) ans.pb(i);
   	}
   	cout << sz(ans) << endl;
   	for (int i: ans) cout << i + 1 << ' ';
}
int main() {
	return 0;
}
