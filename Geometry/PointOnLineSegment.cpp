// boj 9875 Cow Curling
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename PointType>
struct Point {
    PointType x, y;

    Point<PointType> operator + (const Point<PointType>& p) const { return {x + p.x, y + p.y}; }
    Point<PointType> operator - (const Point<PointType>& p) const { return {x - p.x, y - p.y}; }
    PointType operator * (const Point<PointType>& p) const { return x * p.x + y * p.y; } // 내적
    PointType operator / (const Point<PointType>& p) const { return x * p.y - p.x * y; } // 외적

    static PointType Dist(const Point<PointType>& p1, const Point<PointType>& p2) { return (p2 - p1) * (p2 - p1); }
    static PointType SignedArea(const Point<PointType>& p1, const Point<PointType>& p2, const Point<PointType>& p3) { return (p2 - p1) / (p3 - p1); }
    static PointType CCW(const Point<PointType>& p1, const Point<PointType>& p2, const Point<PointType>& p3) { 
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
// 다각형 내부 또는 경계 위에 pt가 있으면 true, O(log N)
// 주의: v는 반시계 방향으로 정렬된 볼록 다각형이어야 함
template<typename PointType>
bool PointInConvexPolygon(const vector<Point<PointType>> &v, Point<PointType> &pt) {
    PointType n = v.size();
    //rightv, leftv의 내부각에 pt가 들어오지 않는다면, 바로 제외. 
    if(Point<PointType>::CCW(v[0], v[1], pt) < 0 || Point<PointType>::CCW(v[0], v.back(), pt) > 0) return false; 
    PointType l = 1, r = n - 1;
    while(l + 1 < r){
        PointType m = (l + r) >> 1;
        if(Point<PointType>::CCW(v[0], v[m], pt) > 0) l = m; else r = m;
    }
    // pt와, pt가 포함되는 section의 변에 대해 CCW 알고리즘을 적용해서 위치 관계를 파악한다. 
    return Point<PointType>::CCW(v[l], pt, v[l + 1]) <= 0 ? true : false;
}
// 선분 위에 점이 있는지 확인하는 함수
template<typename PointType>
bool PointOnLineSegment(const Point<PointType>& a, const Point<PointType>& b, const Point<PointType>& pt) {
    if (Point<PointType>::CCW(a, b, pt) != 0) return false;
    return min(a.x, b.x) <= pt.x && pt.x <= max(a.x, b.x) && min(a.y, b.y) <= pt.y && pt.y <= max(a.y, b.y);
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll N; cin >> N;
    vector<Point<ll>> A(N); vector<Point<ll>> B(N);
    for(int i = 0; i < N; i++) cin >> A[i].x >> A[i].y;
    for(int i = 0; i < N; i++) cin >> B[i].x >> B[i].y;

    vector<Point<ll>> teamAarea = ConvexHull(A);
    vector<Point<ll>> teamBarea = ConvexHull(B);

    ll teamAscore = 0, teamBscore = 0;
    if (teamAarea.size() == 2) {
        // team A 볼록 껍질이 선분인 경우
        for (int i = 0; i < N; i++) {
            if (PointOnLineSegment(teamAarea[0], teamAarea[1], B[i])) teamAscore++;
        }
    } else if (teamAarea.size() > 2) {
        // team A 볼록 껍질이 다각형인 경우
        for (int i = 0; i < N; i++) {
            if (PointInConvexPolygon(teamAarea, B[i])) teamAscore++;
        }
    }

    if (teamBarea.size() == 2) {
        // team B 볼록 껍질이 선분인 경우
        for (int i = 0; i < N; i++) {
            if (PointOnLineSegment(teamBarea[0], teamBarea[1], A[i])) teamBscore++;
        }
    } else if (teamBarea.size() > 2) {
        // team B 볼록 껍질이 다각형인 경우
        for (int i = 0; i < N; i++) {
            if (PointInConvexPolygon(teamBarea, A[i])) teamBscore++;
        }
    }

    cout << teamAscore << " " << teamBscore;
    return 0; 
}
