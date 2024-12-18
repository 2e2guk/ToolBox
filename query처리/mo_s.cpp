//13547 풀이, 가장 많이 등장하는 수, 서로 다른 수의 개수, abs(Ai - Aj) ≤ K인 (i, j) 쌍의 수(펜윅 트리 결합) 등에 사용
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct query{
    int index, s, e;
};

int n, m, sqrtN, cnt;

vector<query> v;

int ans[100001], num[100001], check[1000001];

bool cmp(query &lhs, query &rhs){
    if(lhs.s/sqrtN == rhs.s/sqrtN)    return lhs.e < rhs.e;
    else return lhs.s/sqrtN < rhs.s/sqrtN;
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int s, e;
    cin >> n;
    sqrtN = sqrt(n);

    for(int i = 1; i <= n; i++){
        cin >> num[i];
    }

    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> s >> e;
        v.push_back({i, s, e});
    }
    sort(v.begin(), v.end(), cmp);
    s = v[0].s;
    e = v[0].e;
    
    /*최초 구간 계산하기*/
    for(int i = s; i <= e; i++){
        if(!check[num[i]])    cnt++;
        check[num[i]]++;
    }
    ans[v[0].index] = cnt;
    
    for(int i = 1; i < m; i++){
        while(s < v[i].s){
            /*update(구간 축소)*/
            check[num[s]]--;
            if(!check[num[s]])    cnt--;
            /*------*/
            s++;
        }
        while(v[i].s < s){
            s--;
            /*update(구간 확장)*/
            if(!check[num[s]])    cnt++;
            check[num[s]]++;
            /*------*/
        }
        while(e < v[i].e){
            e++;
            /*update(구간 확장)*/
            if(!check[num[e]])    cnt++;
            check[num[e]]++;
            /*------*/
        }
        while(v[i].e < e){
            /*update(구간 축소)*/                                                                             
            check[num[e]]--;
            if(!check[num[e]])    cnt--;
            /*------*/
            e--;
        }
        ans[v[i].index] = cnt; //쿼리에 대한 정답 저장
    }
    
    for(int i = 0; i < m; i++) 
        cout << ans[i] << "\n";
    
    return 0;
}
