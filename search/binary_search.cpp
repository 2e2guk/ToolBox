// binary search
// 찾고자 하는 값이 있으면 그 값을 출력하고, 없으면 -1을 출력한다.  
#include <bits/stdc++.h>

using namespace std;

// 이분 탐색, return value는 찾고자 하는 값의 index.
int binary_search(vector<int>& a, int m) {
    int l = 0, r = a.size() - 1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(a[mid] == m) return mid;
        else if(a[mid] < m) l = mid + 1;
        else if(a[mid] > m) r = mid - 1;
    }
    // 검색 실패에 해당하는 경우.
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    // n = 입력배열의 크기, m = 찾고자하는 값.
    int n, m; cin >> n >> m;
    vector<int> a(n, 0);
    for(int i = 0; i < n; i++) cin >> a[i];
    // 이분탐색은 정렬된 환경에서만 가능
    sort(a.begin(), a.end());
    int searchres = binary_search(a, m);
    if(searchres != -1) cout << a[searchres];
    else cout << searchres;
    return 0;
}
