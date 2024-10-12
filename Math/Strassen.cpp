/*
Strassen's algorithm
O(r^(log7=2.81)) nxm * mxk 행렬곱에서 max(n,m,k)에 가장가깝고 더 큰 2^x값이 r이 된다
정사각 행렬을
큰 차원의 행렬에서 기존의 O(n^3)보다 조금 더 빠름
main함수 예제는 BOJ 2704
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<ll>> Matrix;

// 행렬 덧셈
Matrix add(const Matrix &A, const Matrix &B) {
    ll n = A.size();
    ll m = A[0].size();
    Matrix C(n, vector<ll>(m, 0));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// 행렬 뺄셈
Matrix subtract(const Matrix &A, const Matrix &B) {
    ll n = A.size();
    ll m = A[0].size();
    Matrix C(n, vector<ll>(m, 0));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// 행렬 크기를 2^n 크기로 맞추는 함수
Matrix resizeMatrix(const Matrix &A, ll newSize) {
    ll oldRows = A.size();
    ll oldCols = A[0].size();
    Matrix resized(newSize, vector<ll>(newSize, 0));

    for (ll i = 0; i < oldRows; ++i) {
        for (ll j = 0; j < oldCols; ++j) {
            resized[i][j] = A[i][j];
        }
    }
    return resized;
}

// Strassen 알고리즘을 사용한 행렬 곱셈
Matrix strassen(const Matrix &A, const Matrix &B) {
    ll n = A.size();

    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    // 행렬을 4개의 하위 블록으로 나눔
    ll half = n / 2;
    Matrix A11(half, vector<ll>(half)), A12(half, vector<ll>(half)),
           A21(half, vector<ll>(half)), A22(half, vector<ll>(half)),
           B11(half, vector<ll>(half)), B12(half, vector<ll>(half)),
           B21(half, vector<ll>(half)), B22(half, vector<ll>(half));

    // 행렬 분할
    for (ll i = 0; i < half; ++i) {
        for (ll j = 0; j < half; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // Strassen의 7개의 중간 행렬 계산
    Matrix M1 = strassen(add(A11, A22), add(B11, B22));
    Matrix M2 = strassen(add(A21, A22), B11);
    Matrix M3 = strassen(A11, subtract(B12, B22));
    Matrix M4 = strassen(A22, subtract(B21, B11));
    Matrix M5 = strassen(add(A11, A12), B22);
    Matrix M6 = strassen(subtract(A21, A11), add(B11, B12));
    Matrix M7 = strassen(subtract(A12, A22), add(B21, B22));

    // 결과 행렬 조합
    Matrix C(n, vector<ll>(n, 0));
    for (ll i = 0; i < half; ++i) {
        for (ll j = 0; j < half; ++j) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];           // C11
            C[i][j + half] = M3[i][j] + M5[i][j];                           // C12
            C[i + half][j] = M2[i][j] + M4[i][j];                           // C21
            C[i + half][j + half] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j]; // C22
        }
    }

    return C;
}

// 새로운 함수: 행렬 크기 맞추기 및 Strassen 알고리즘 실행
Matrix prepareAndExecuteStrassen(const Matrix &A, const Matrix &B, ll N, ll M, ll K) {
    // 행렬 크기를 2의 제곱수로 맞추기 위해 새로운 크기 계산
    ll maxSize = max({N, M, K});
    ll newSize = 1;
    while (newSize < maxSize) newSize *= 2;

    // 행렬 크기를 2^n 크기로 맞추기 위한 함수 호출
    Matrix A_resized = resizeMatrix(A, newSize);
    Matrix B_resized = resizeMatrix(B, newSize);

    // Strassen 알고리즘 실행
    Matrix C_resized = strassen(A_resized, B_resized);

    // 결과 행렬을 원래의 크기로 자르기
    Matrix C_final(N, vector<ll>(K, 0));
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < K; ++j) {
            C_final[i][j] = C_resized[i][j];
        }
    }

    return C_final;
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
    Matrix C = prepareAndExecuteStrassen(A, B, N, M, K);

    // 결과 출력
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < K; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}