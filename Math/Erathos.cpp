//1~n까지의 소수를 빠르게 찾는 알고리즘
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void erathos(vector<int> &result, int n){
    vector<bool> notPrime(n + 1, false);

    notPrime[1] = true;
    for(int i = 2; i <= sqrt(n); i++){
        if(notPrime[i]) continue;
        for(int j = (i << 1); j <= n; j += i){
            notPrime[j] = true;
        }
    }

    for(int i = 1; i <= n; i++){
        if(!notPrime[i])    result.emplace_back(i);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll n; cin >> n;
    vector<int> primeList;
    erathos(primeList, n);

    for(int x : primeList){
        cout << x << " ";
    }
    return 0;
}