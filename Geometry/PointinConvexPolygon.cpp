// 볼록 다각형 내에 점이 있는지 없는지 판별
// convexhull 호출하고 사용시, K개의 점의 내/외부 판단 : O(max(N, K) log N)
// 애초에 볼록다각형이 올바르게 정렬되어 제공, K개의 점의 내/외부 판단 : O(K log N)
// main 함수 사용 예시는 boj 11686
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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll L; cin >> L;
    vector<Point<ll>> large(L);
    for(ll i = 0; i < L; i++) cin >> large[i].x >> large[i].y;
    
    // 대형 스카이 랜턴의 위치로 볼록 껍질을 생성
    vector<Point<ll>> convexHull = ConvexHull(large);

    ll S; cin >> S;
    ll count = 0; // 내부에 있는 작은 스카이 랜턴의 수를 센다. 
    for(ll i = 0; i < S; i++) {
        Point<ll> p; cin >> p.x >> p.y;
        // 각 작은 스카이 랜턴이 볼록 껍질 내부에 있는지 확인
        if (PointInConvexPolygon(convexHull, p)) count++;
    }
    // 결과 출력
    cout << count;
    return 0;
}
