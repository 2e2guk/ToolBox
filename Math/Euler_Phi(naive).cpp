// 오일러 피 함수(naive)
// O(sqrt(N))
// main 함수 사용 예시는 boj 11689 
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template<typename T>
T eulerPhi(T n) {
    T ans = n;
    T num = n;
    for (T i = 2; i * i <= n; ++i) {
        if (num % i == 0) {
            ans /= i;
            ans *= i - 1;
            while (num % i == 0) {
                num /= i;
            }
        }
    }

    if (num != 1) {
        ans /= num;
        ans *= num - 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll n; cin >> n;
    cout << eulerPhi(n);
    return 0;
}
