// KMP 알고리즘(문자열 패턴 매칭 알고리즘)
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
// a에서, b가 몇 번 등장하는지를 구하는 kmp 함수. 
// 0-index이므로, 1부터 인덱스가 시작한다면, match_indice에 1을 더해 줘야 한다. 
vector<int> kmp(const string &a, const string &b) {
    int sz_a = a.length(); int sz_b = b.length();
    vector<int> fail = kmp_fail(b), match_indice;
    for (int i = 0, j = 0; i < sz_a; i++) {
        while (j && a[i] != b[j]) j = fail[j - 1];
        if (a[i] == b[j]) {
        if (j == sz_b - 1) {
            match_indice.push_back(i - sz_b + 1);
            j = fail[j];
        } else {
            j++;
        }
        }
    }
    return match_indice;
}
int main(){
    return 0;
}
