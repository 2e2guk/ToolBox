// convex hull(볼록 껍질) + CCW
// Graham Scan, O(N log N) 
// 변 위에 여러 개의 점이 있다면, 제거한다. 곧, convex hull을 이루는 최소 개수의 정점을 구한다.  
// main 함수 사용예시는 boj 1708
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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    vector<Point<ll>> points(N, Point<ll>());
    for(int i = 0; i < N; i++) cin >> points[i].x >> points[i].y;
    vector<Point<ll>> ans = ConvexHull(points);
    cout << ans.size();
    return 0;
}
