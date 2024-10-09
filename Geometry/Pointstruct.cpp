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
