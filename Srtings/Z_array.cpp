//S[i...] 의 prefix 들 중 S의 prefix이기도 한 녀석들 중 길이가 가장 긴 것의 길이에 대한 배열을 O(N)에 구하기
#include <bits/stdc++.h>

using namespace std;

void getZarray(vector<int> &zValue, string str){
    int n = str.size(), l = 0, r = 0;
    zValue.resize(str.size() + 1);

    reverse(str.begin(), str.end());
	zValue[0] = str.size();
	for(int i = 1; i < n; i++){
        if(r < i){
            zValue[i] = 0;
            while(str[zValue[i]] == str[i + zValue[i]]) zValue[i]++;
            l = i;
            r = i + zValue[i] - 1;
        }
        else{
            if(zValue[i - l] <= r - i)	zValue[i] = zValue[i - l];
			else{
                zValue[i] = r - i + 1;
				while(str[zValue[i]] == str[i + zValue[i]]) zValue[i]++;
				l = i;
				r = i + zValue[i] - 1;
			}
        }
	}
}

int main(){
    int q, x;
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    string str;
    vector<int> result;
    cin >> str;
    getZarray(result, str);
    cin >> q;
    while(q--){
        cin >> x;
        cout << result[str.size() - x] << '\n';
    }
    return 0;
}