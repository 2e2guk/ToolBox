// boj 15336 Homework
// Dinic + 이분탐색
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MAXN = 1202;

struct maxFlow {
	struct edge{ 
        int pos, cap, rev; 
    };
	vector<edge> g[MAXN];
	void add_edge(int s, int e, int val) {
		g[s].push_back({e, val, (int)g[e].size()});
		g[e].push_back({s, 0, (int)g[s].size()-1}); // 역방향 간선
	}
	int dis[MAXN], pnt[MAXN];
	bool augmenting_path(int src, int sink) {
		memset(dis, 0, sizeof(dis));
		memset(pnt, 0, sizeof(pnt));
		queue<int> q;
		q.push(src);
		dis[src] = 1;
		while(!q.empty()) {
			int x = q.front();
			q.pop();
			for(auto &e : g[x]) {
				if(e.cap > 0 && !dis[e.pos]) {
					dis[e.pos] = dis[x] + 1;
					q.push(e.pos);
				}
			}
		}
		return dis[sink] > 0;
	}
	int sendFlow(int x, int sink, int f) {
		if(x == sink) return f;
		for(; pnt[x] < g[x].size(); pnt[x]++) {
			edge e = g[x][pnt[x]];
			if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
				int w = sendFlow(e.pos, sink, min(f, e.cap));
				if(w) {
					g[x][pnt[x]].cap -= w;
					g[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}
	ll DinicMaxFlow(int src, int sink) {
		ll ret = 0;
		while(augmenting_path(src, sink)) {
			int r;
			while((r = sendFlow(src, sink, 2e9))) ret += r;
		}
		return ret;
	}
};

int max_assignment(vector<pi> c){
	sort(c.begin(), c.end(), [&](const pi &a, const pi &b) {
		return a.first < b.first;
	});
	int p = 0;
	int ans = 0;
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 1; i <= 400; i++) {
		while(p < (int)c.size() && c[p].first == i) {
			pq.push(c[p++].second);
		}
		while(!pq.empty() && pq.top() < i) pq.pop();
		if(!pq.empty()) {
			ans++;
			pq.pop();
		}
	}
	return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
	int n, m; cin >> n >> m;
    maxFlow mf;
	vector<pi> c;
    // 각 과제의 시작, 종료일 입력
	for(int i = 0; i < n; i++) {
		int x, y; cin >> x >> y; 
		c.push_back({x, y});
	}
	cout << max_assignment(c) << "\n";
    int src = 0, sink = MAXN - 1;
	for(int i = 0; i < n; i++) {
		if(i < m) {
			mf.add_edge(src, i + 1, 1);
			for(int j = c[i].first; j <= c[i].second; j++) {
				mf.add_edge(i + 1, j + n, 1);
			}
		} else {
			mf.add_edge(i + 1, sink, 1);
			for(int j = c[i].first; j <= c[i].second; j++) {
				mf.add_edge(j + n + 400, i + 1, 1);
			}
		}
	}
	for(int i = 1; i <= 400; i++) {
		mf.add_edge(n + i, n + i + 400, 1);
	}
	cout << mf.DinicMaxFlow(src, sink) << "\n";
    return 0;
}
