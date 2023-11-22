// Roating Calipers(회전하는 캘리퍼스)
// 점 집합들에서, 가장 먼 두 점을 구한다. <- 점 집합에서 가장 먼 두 점은, convex hull 위에 있다. 
// O(N)
// main 함수 사용 예시는 boj 10254
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename PointType>
struct Point {
    PointType x, y;

    Point operator + (const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator - (const Point& p) const { return {x - p.x, y - p.y}; }
    PointType operator * (const Point& p) const { return x * p.x + y * p.y; } // 내적
    PointType operator / (const Point& p) const { return x * p.y - p.x * y; } // 외적

    static PointType Dist(const Point& p1, const Point& p2) { return (p2 - p1) * (p2 - p1); }
    static PointType SignedArea(const Point& p1, const Point& p2, const Point& p3) { return (p2 - p1) / (p3 - p1); }
    static PointType CCW(const Point& p1, const Point& p2, const Point& p3) { 
        PointType area = SignedArea(p1, p2, p3);
        return (area > 0) - (area < 0);
    }
};

template<typename PointType>
vector<Point<PointType>> ConvexHull(vector<Point<PointType>> points) {
    if (points.size() <= 1) return points;
    swap(points[0], *min_element(points.begin(), points.end(), [](const Point<PointType>& a, const Point<PointType>& b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    }));
    sort(points.begin() + 1, points.end(), [&](const Point<PointType>& a, const Point<PointType>& b) {
        int dir = Point<PointType>::CCW(points[0], a, b);
        if (dir != 0) return dir > 0;
        return Point<PointType>::Dist(points[0], a) < Point<PointType>::Dist(points[0], b);
    });
    vector<Point<PointType>> hull;
    for (const auto& p : points) {
        while (hull.size() >= 2 && Point<PointType>::CCW(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }
    return hull;
}
// 주의: hull은 반시계 방향으로 정렬된 볼록 다각형이어야 함
template<typename PointType>
pair<Point<PointType>, Point<PointType>> Calipers(vector<Point<PointType>> hull){
    int n = hull.size(); PointType mx = 0; Point<PointType> a, b;
    for(int i=0, j=0; i<n; i++){
        while(j + 1 < n && (hull[i+1] - hull[i]) / (hull[j+1] - hull[j]) >= 0){
            PointType now = Point<PointType>::Dist(hull[i], hull[j]);
            if(now > mx) mx = now, a = hull[i], b = hull[j];
            j++;
        }
        PointType now = Point<PointType>::Dist(hull[i], hull[j]);
        if(now > mx) mx = now, a = hull[i], b = hull[j];
    }
    return {a, b};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int tc; cin >> tc;
    while(tc--) {
        int N; cin >> N;
        vector<Point<ll>> points(N, Point<ll>());
        for(int i = 0; i < N; i++) cin >> points[i].x >> points[i].y;
        pair<Point<ll>, Point<ll>> ans = Calipers(ConvexHull(points));
        cout << ans.first.x << " " << ans.first.y << " " << ans.second.x << " " << ans.second.y << "\n";
    }
    return 0;
}
