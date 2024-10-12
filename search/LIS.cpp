//LIS 크기 및 무작위 예시 1개를 찾음
#include <bits/stdc++.h>

using namespace std;

const int MAXSIZE = 1e6;

int num[MAXSIZE + 1];
int trace[MAXSIZE + 1]; //무작위 예시 찾기

vector<int> v;
vector<int> LIS; //무작위 예시 찾기

int n, sizeofLIS;

int main(){
    cin.tie(NULL);  ios::sync_with_stdio(false);

    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> num[i];
    }

    for(int i = 0; i < n; i++){
        if(v.empty() || num[i] > v.back()){
			v.push_back(num[i]);
			trace[i] = v.size(); //무작위 예시 찾기
		}
		else{
			auto t = lower_bound(v.begin(), v.end(), num[i]);
			*t = num[i];
			trace[i] = t - v.begin() + 1;  //무작위 예시 찾기
		}
    }

    sizeofLIS = v.size();

    /*-----무작위 예시를 찾을 때 사용-----*/
    int idx = v.size();
    for(int i = n - 1; i >= 0; i--){
        if(trace[i] == idx){
            idx--;
            LIS.push_back(num[i]);
        }
    }
    reverse(LIS.begin(), LIS.end());
    /*---------------------------------*/

    cout << sizeofLIS << '\n';
    for(int x : LIS){
        cout << x << ' ';
    }

    return 0;
}