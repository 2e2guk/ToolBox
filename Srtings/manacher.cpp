//가장 긴 팰린드롬을 O(n)에 찾는 알고리즘 
#include <bits/stdc++.h>

using namespace std;

int manacher(string inputStr){
    int strLen = inputStr.size(), r = 0, p = 0, ret = 0;
    string str = " ";
	for(int i = 0; i < strLen; i++){
		str += inputStr[i];
		str += " ";
	}
    strLen = str.size();
    vector<int> A(strLen + 1);
    for(int i = 0; i < strLen; i++){
		if(i <= r)	A[i] = min(r - i, A[2 * p - i]);
		while(0 <= i - A[i] - 1 && i + A[i] + 1 < strLen && str[i - A[i] - 1] == str[i + A[i] + 1]) A[i]++;
		if(r < i + A[i]){
			r = i + A[i];
			p = i;
		}
	}

    for(int i = 1; i <= strLen; i++){
		ret = max(ret, A[i]);
	}

    return ret;
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    string input;
    cin >> input;
    cout << manacher(input);
    return 0;
}