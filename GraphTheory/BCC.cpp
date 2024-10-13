//단절점 탐색 dfs
//root 이면서 자식 수 2개 이상, 해당 정점을 거치지 않고 빠른 방문 번호를 가진 정점으로 이동 불가
#include <bits/stdc++.h>

using namespace std;

const int MAXSIZE = 1e4 + 1;
int v, e;

vector<int> graph[MAXSIZE];
vector<int> ans;
int visited[MAXSIZE], cnt; //방문 여부 및 순서 저장
bool isArt[MAXSIZE]; //단절점(Articulation Point) 여부 저장

int dfs(int cur, bool isRoot){
	visited[cur] = ++cnt; //정점 방문 순서 저장
	int ret = visited[cur], prev, child = 0;
	for(int next : graph[cur]){
		if(!visited[next]){
			child++;
			prev = dfs(next, false);
			ret = min(ret, prev);
            //자식 노드들이 정점 A를 거치지 않고 정점 A보다 빠른 방문번호를 가진 정점으로 이동 불가
			if(!isRoot && prev >= visited[cur]){//해당 조건을 만족시 cur-next는 단절선
				isArt[cur] = true;
			}
		}
		else{
			ret = min(ret, visited[next]);
		}
	}
    //단절선 찾으려면 필요 없음
	if(isRoot && child >= 2){//루트 node이고 자식의 수가 2개 이상이면
		isArt[cur] = true;
	}
	return ret;
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> v >> e;
	int x, y;
	for(int i = 0; i < e; i++){
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	for(int i = 1; i <= v; i++) {
		if(!visited[i])	dfs(i, true);
	}
	
	for(int i = 1; i <= v; i++) {
		if(isArt[i])	ans.push_back(i);
	}
	
	sort(ans.begin(), ans.end());
	cout << ans.size() << "\n";
	for(int p : ans){
		cout << p << " ";
	}
    return 0;
}