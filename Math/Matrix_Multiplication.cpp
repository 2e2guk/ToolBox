/*
단순 삼중for문
O(n^3)행렬곱셈
main함수 예제는 BOJ 2704
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

typedef vector<vector<ll>> Matrix;

// 행렬 곱셈 함수
Matrix multiply(const Matrix &A, const Matrix &B) {
    ll n = A.size();         // A의 행의 개수
    ll m = B[0].size();      // B의 열의 개수
    ll k = A[0].size();      // A의 열의 개수, B의 행의 개수와 같아야 함

    // 결과 행렬 C 초기화 (n x m 크기)
    Matrix C(n, vector<ll>(m, 0));

    // 행렬 곱셈 수행
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int l = 0; l < k; ++l) {
                C[i][j] += A[i][l] * B[l][j];
            }
        }
    }

    return C;
}
// 행렬 곱셈 문제 해결을 위한 main 함수
int main() {
    ll N, M, K;
    
    // 행렬 A 입력 받기
    cin >> N >> M;
    Matrix A(N, vector<ll>(M));
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < M; ++j) {
            cin >> A[i][j];
        }
    }

    // 행렬 B 입력 받기
    cin >> M >> K;
    Matrix B(M, vector<ll>(K));
    for (ll i = 0; i < M; ++i) {
        for (ll j = 0; j < K; ++j) {
            cin >> B[i][j];
        }
    }

    // 행렬 크기를 맞추고 Strassen 알고리즘 실행
    Matrix C = multiply(A, B);

    // 결과 출력
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < K; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
