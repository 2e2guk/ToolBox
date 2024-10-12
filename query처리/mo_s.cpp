// 임시코드
#include <bits/stdc++.h>

using namespace std;

struct query{
    int index, s, e;
};

int n, m, sqrtN, cnt;

vector<query> v;

int ans[100001], num[100001];
int check[1000001];

bool cmp(query &lhs, query &rhs){
    if(lhs.s/sqrtN == rhs.s/sqrtN)    return lhs.e < rhs.e;
    else return lhs.s/sqrtN < rhs.s/sqrtN;
}

int main(){
    int s, e;
    cin.tie(0);
    ios::sync_with_stdio(0);
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
    
    for(int i = s; i <= e; i++){
        if(!check[num[i]])    cnt++;
        check[num[i]]++;
    }
    ans[v[0].index] = cnt;
    
    for(int i = 1; i < m; i++){
        
        while(s < v[i].s){
            check[num[s]]--;
            if(!check[num[s]])    cnt--;
            s++;
        }
        
        while(v[i].s < s){
            s--;
            if(!check[num[s]])    cnt++;
            check[num[s]]++;
        }
        
        while(e < v[i].e){
            e++;
            if(!check[num[e]])    cnt++;
            check[num[e]]++;
        }
        
        while(v[i].e < e){                                                                             
            check[num[e]]--;
            if(!check[num[e]])    cnt--;
            e--;
        }
        
        ans[v[i].index] = cnt;
    }
    
    for(int i = 0; i < m; i++) 
        cout << ans[i] << "\n";
    
    return 0;
}
