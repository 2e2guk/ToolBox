// 평방 분할(제곱근 분할법, sqrt decomposition)
// 주어진 쿼리를, O(sqrt(N))개의 그룹으로 분할해 결과를 구한다. -> 시간복잡도  O(sqrt(N))
// 0-based, main 함수 예시는 boj 14504
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename ValueType>
struct SqrtDecomposition {
    vector<ValueType> arr;
    vector<vector<ValueType>> buckets;
    ll sq;

	SqrtDecomposition(ll n, const vector<ValueType>& input) : arr(input) {
        sq = sqrt(n);
        buckets.resize((n + sq - 1) / sq); // 올림 처리를 통한 크기 설정
        for(ll i = 0; i < n; i++){
            buckets[i / sq].push_back(arr[i]);
        }
		// 이 부분은, 문제에 따라서 추가한 부분이다. 
        for(ll i = 0; i < buckets.size(); i++) { // buckets.size()를 사용
            sort(buckets[i].begin(), buckets[i].end());
        }
    }

    void update(ll idx, ValueType val) {
        ll id = idx / sq; // 그룹 번호
        auto &bucket = buckets[id];
        auto it = lower_bound(bucket.begin(), bucket.end(), arr[idx]);
        bucket.erase(it);
        bucket.insert(upper_bound(bucket.begin(), bucket.end(), val), val);
        arr[idx] = val;
    }

    ValueType query(ValueType l, ValueType r, ValueType k) {
        ValueType ret = 0;
        while(l % sq != 0 && l <= r) {
            if(arr[l] > k) ret++;
            l++;
        } 
        while((r + 1) % sq != 0 && l <= r) {
            if(arr[r] > k) ret++;
            r--;
        } 
        while(l <= r){
            ret += buckets[l / sq].end() - upper_bound(buckets[l / sq].begin(), buckets[l / sq].end(), k);
            l += sq;
        }
        return ret;
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll n, m; cin >> n;
    vector<ll> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    SqrtDecomposition<ll> root(n, arr);
	
    cin >> m;
    for(int i = 0; i < m; i++){
        int a; cin >> a;
        if(a == 2) {
            ll b, c; cin >> b >> c; b--;
            root.update(b, c);
        } else {
            ll l, r, val; cin >> l >> r >> val; l--; r--;
            cout << root.query(l, r, val) << "\n";
        }
    }
    return 0;
}
