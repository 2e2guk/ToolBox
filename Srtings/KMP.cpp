// 일대일 문자열 패턴 매칭 알고리즘
// main 함수 사용 예시는 boj 1786
// KMP 
// 문자열 S, 패턴 P라면, O(S + P) 시간에 찾는다. 
#include <bits/stdc++.h>
using namespace std;

// 입력 문자열 s의 실패 함수 값을 구해 주는 함수. 
vector<int> kmp_fail(const string &s) {
    int sz = s.length();
    vector<int> fail(sz);

    for (int i = 1, j = 0; i < sz; i++) {
        while (j && s[i] != s[j]) j = fail[j - 1];
        if (s[i] == s[j]) fail[i] = ++j;
    }
    return fail;
}
// S에서, P가 몇 번 등장하는지를 구하는 kmp 함수. 
// 0-index이므로, 1부터 인덱스가 시작한다면, match_index에 1을 더해 줘야 한다. 
vector<int> kmp(const string &a, const string &b) {
    int sz_a = a.length(); int sz_b = b.length();
    vector<int> fail = kmp_fail(b), match_index;
    for (int i = 0, j = 0; i < sz_a; i++) {
        while (j && a[i] != b[j]) j = fail[j - 1];
        if (a[i] == b[j]) {
            if (j == sz_b - 1) {
                match_index.push_back(i - sz_b + 1);
                j = fail[j];
            } else j++;
        }
    }
    return match_index;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    string S, W;
    getline(cin, S); getline(cin, W);
    vector<int> res = kmp(S, W);
    cout << res.size() << "\n";
    for(const auto& ele : res) cout << ele + 1 << "\n";
    return 0;
}
