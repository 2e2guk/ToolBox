//dp[t][i]=min{k<i}(dp[t-1][k]+C[k][i])
//K[t][i]는 dp[t][i]를 만족시키는 최소 k라 할 때 다음 부등식을 만족 K[t][i]≤K[t][i+1]
//혹은 비용 C에 대해 C[a][c]+C[b][d]<=C[a][d]+C[b][c]
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = 1e18;
int L, G, K[801][8001];
ll psum[8001], C[801][1001];
ll dp[801][8001], ans;
//dncOpt 기본형, dp[mid] < (i - mid) * t[i] + v[mid]처럼 t가 없는 경우도 가능
void dncOptOriginal(int t, int s, int e, int optS, int optE){ 
    // dp[t][s], dp[t][s+1], ..., dp[t][e]를 계산하는 함수. [optS, optE] 가능한 k의 범위
    if(s > e) return;
        int mid = s + e>> 1;
        dp[t][mid] = 1e18;
        for (int k = optS; k <= optE && k < mid; k++){// dp[t][m]에 대해 가능한 답을 선형 시간에 계산
            ll value = dp[t-1][k] + C[k][mid];
            if (dp[t][mid] > value)
                dp[t][mid] = value, K[t][mid] = k;
        }
        //dp[t][s], ..., dp[t][m-1]에 대해서 계산하기 위한 재귀 호출
        dncOptOriginal(t, s, mid - 1, optS, K[t][mid]);
        //dp[t][m+1], ..., dp[t][e]에 대해서 계산하기 위한 재귀 호출
        dncOptOriginal(t, mid + 1, e, K[t][mid], optE);
        // 2, 3에 대해 가능한 k의 후보는 조건에 의해 줄어든다.
}
//13261 풀이
void dncOptEx(int t, int s, int e, int optS, int optE){
	if(s > e)	return;
	int mid = s + e >> 1;
	int opt = 0;
	dp[t][mid] = 1e18;
	for(int i = optS; i <= min(mid, optE); i++){
		if(dp[t][mid] > dp[t - 1][i] + (mid - i) * (psum[mid] - psum[i])){
			dp[t][mid] = dp[t - 1][i] + (mid - i) * (psum[mid] - psum[i]);
			opt = i;
		}
	}
	dncOptEx(t, s, mid - 1, optS, opt);
	dncOptEx(t, mid + 1, e, opt, optE);
}

int main(){
	int x;
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cin >> L >> G;
	for(int i = 1; i <= L; i++){
		cin >> x;
		psum[i] = psum[i - 1] + x;
		dp[1][i] = psum[i] * i;
	}
	for(int i = 2; i <= G; i++){
		dncOptEx(i, 1, L, 1, L);
	}
	cout << dp[G][L];
	return 0;
}
