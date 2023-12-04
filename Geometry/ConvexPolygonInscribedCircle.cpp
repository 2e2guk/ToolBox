// Half Plane Intersection(반평면 교집합)
// main 함수 사용 예시는, boj 3903 + 볼록 다각형의 내접원의 반지름과, 중심점의 좌표를 구해 출력한다. 
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
typedef pair<long double, long double> pi;

bool z(long double x){ return fabs(x) < eps; }

long double ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

struct line {
	long double a, b, c;
	bool operator<(const line &l)const{
		bool flag1 = pi(a, b) > pi(0, 0);
		bool flag2 = pi(l.a, l.b) > pi(0, 0);
		if(flag1 != flag2) return flag1 > flag2;
		long double t = ccw(pi(0, 0), pi(a, b), pi(l.a, l.b));
		return z(t) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : t > 0;
	}
	pi slope(){ return pi(a, b); }
};

pi cross(line a, line b){
	long double det = a.a * b.b - b.a * a.b;
	return pi((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
}

bool bad(line a, line b, line c){
	if(ccw(pi(0, 0), a.slope(), b.slope()) <= 0) return false;
	pi crs = cross(a, b);
	return crs.first * c.a + crs.second * c.b >= c.c;
}

bool HPI(vector<line> v, vector<pi> &solution){ // ax + by <= c;
	sort(v.begin(), v.end());
	deque<line> dq;
	for(auto &i : v){
		if(!dq.empty() && z(ccw(pi(0, 0), dq.back().slope(), i.slope()))) continue;
		while(dq.size() >= 2 && bad(dq[dq.size()-2], dq.back(), i)) dq.pop_back();
		while(dq.size() >= 2 && bad(i, dq[0], dq[1])) dq.pop_front();
		dq.push_back(i);
	}
	while(dq.size() > 2 && bad(dq[dq.size()-2], dq.back(), dq[0])) dq.pop_back();
	while(dq.size() > 2 && bad(dq.back(), dq[0], dq[1])) dq.pop_front();
	vector<pi> tmp;
	for(int i=0; i<dq.size(); i++){
		line cur = dq[i], nxt = dq[(i+1)%dq.size()];
		if(ccw(pi(0, 0), cur.slope(), nxt.slope()) <= eps) return false;
		tmp.push_back(cross(cur, nxt));
	}
	solution = tmp;
	return true;
}
// 선분을 내부 방향으로 이동시키는 함수
line moveLineInside(line l, long double d) {
    // l의 방향에 수직인 벡터를 계산
    long double dx = -l.b;
    long double dy = l.a;
    long double len = hypot(dx, dy);
    dx /= len;
    dy /= len;
    // 선분을 d 거리만큼 이동시킴
    l.c -= d * len;
    return l;
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    while(cin >> n && n) {
        vector<pi> points(n);
        for(int i = 0; i < n; ++i) {
            cin >> points[i].first >> points[i].second;
        }
        
        long double lo = 0, hi = 10000, mid;
        while(hi - lo > eps) {
            mid = (lo + hi) / 2;
            vector<line> lines;
            for(int i = 0; i < n; ++i) {
                int j = (i + 1) % n;
                line l = {points[j].second - points[i].second, points[i].first - points[j].first, points[i].first * points[j].second - points[j].first * points[i].second};
                lines.push_back(moveLineInside(l, mid));
            }
            vector<pi> solution;
            if(HPI(lines, solution)) lo = mid;
            else hi = mid;
        }

        // 최종 교차점 집합에서 중심 좌표 찾기
        vector<line> finalLines;
        for(int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            line l = {points[j].second - points[i].second, points[i].first - points[j].first, points[i].first * points[j].second - points[j].first * points[i].second};
            finalLines.push_back(moveLineInside(l, lo));
        }
        vector<pi> finalSolution;
        HPI(finalLines, finalSolution);

        long double centerX = 0, centerY = 0;
        for(auto &p : finalSolution) {
            centerX += p.first;
            centerY += p.second;
        }
        centerX /= finalSolution.size();
        centerY /= finalSolution.size();
        cout << fixed << setprecision(6) << lo << " coordinate(x, y) : (" << centerX << ", " << centerY << ")\n";
    }
}
