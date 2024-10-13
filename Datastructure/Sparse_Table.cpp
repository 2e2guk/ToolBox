/*
Sparse Table
table의 계산(전처리)은 Θ(N·log(K))만큼의 시간/공간을 소요
solve(v, k)의 문제 해결은 Θ(log(K))만큼의 시간을 소요
BOJ 17435
합성함수 문제예제
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200000;
const int MAX_LOG_K = 19; // n의 최대값이 500,000이므로 2^19 > 500,000

int table[MAX_LOG_K + 1][MAX_N + 1];
/*
다음은 이론 대로 코딩한 것
공간복잡도를 줄이기 위해 init 코드로 변경
MAX_K -> MAX_LOG_K

// 그래프가 nxt[1...N]에 주어져 있다고 가정.

// table[k][v]: v에서 k번 진행했을 때 도달하는 지점
int table[MAX_K+1][MAX_N+1];

// k=1인 경우 채우기
for (int i = 1; i <= N; ++i) {
    table[1][i] = nxt[i];
}

// k>1인 경우, k를 두 배씩 키워가기
for (int k = 2; k <= MAX_K; k *= 2) {
    for (int i = 1; i <= N; ++i) {
        int tmp = table[k/2][i];
        
        table[k][i] = table[k/2][tmp];
    }
}
*/
// table 생성 함수
void init(int m, const vector<int>& nxt) {
    // k=0, 한 칸 이동하는 경우 초기화
    for (int i = 1; i <= m; ++i) {
        table[0][i] = nxt[i];
    }

    // k>0인 경우, 2^k번 이동한 결과를 계산
    for (int k = 1; k <= MAX_LOG_K; ++k) {
        for (int i = 1; i <= m; ++i) {
            int tmp = table[k - 1][i];
            table[k][i] = table[k - 1][tmp];
        }
    }
}

// 쿼리 처리 함수
int solve(int v, int k) {
    for (int i = MAX_LOG_K; i >= 0; --i) {
        if (k & (1 << i)) {
            v = table[i][v];
        }
    }
    return v;
}

int main() {
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int m;
    cin >> m;

    // 함수 f(i)를 입력받아 nxt 배열에 저장
    vector<int> nxt(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> nxt[i];
    }

    // table 생성
    init(m, nxt);

    int Q;
    cin >> Q;
    while (Q--) {
        int n, x;
        cin >> n >> x;
        int result = solve(x, n);
        cout << result << '\n';
    }

    return 0;
}