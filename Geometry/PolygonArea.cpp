// 다각형의 넓이를 구한다. 
// O(N), kahan's summation 적용해서 정밀도 향상
// main 함수 사용 예시는 boj 2166
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

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
/* -> convexhull 구하는 함수.
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
*/
// 주어진 다각형의 넓이의 2배를 반환. -> kahan's summation 적용해 정밀도 향상
// 누적 오차를 줄여서, 상당한 정밀도 보장.
template<typename PointType>
PointType PolygonArea(const vector<Point<PointType>> &v){
    PointType res = 0, c = 0;  // 누적 합과 오차 보정값
    for (int i = 0; i < v.size(); i++) {
        PointType y = v[i] / v[(i + 1) % v.size()] - c;  // 다음 요소와 오차 보정
        PointType t = res + y;  // 중간 합계
        c = (t - res) - y;  // 다음 계산을 위한 오차 보정값 업데이트
        res = t;  // 누적 합계 업데이트
    }
    return res < 0 ? -res : res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    vector<Point<ld>> points(N, {0, 0});
    for(int i = 0; i < N; i++) cin >> points[i].x >> points[i].y;
    cout << fixed; cout << setprecision(1);
    cout << PolygonArea(points) / 2.0;
    return 0;
}
