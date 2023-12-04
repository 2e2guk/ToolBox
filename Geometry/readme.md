# (계산)기하 알고리즘 #
1. convex hull + CCW -> Graham's Scan
2. Rotating Calipers -> 점 집합에서 가장 먼 두 점은, convex hull 위에 있다.
3. PolygonArea - 다각형 면적 구하기. kahan's sumation 적용해 정밀도 향상.
4. Point in Convex Polygon - 볼록다각형 내의 점 판정.
5. PointOnLineSegment - 선분 위에 점이 있는지 확인.
6. Point in polygon - 일반적인 다각형 내의 점 판정
7. Shamos-Hoey - N개의 선분이 주어졌을 때, 이 선분들이 서로 교차하는지 아닌지를 판별.
8. segment intersect - 선분 교차 판정 - Shamos-Hoey.cpp 코드 내에 존재. 
9. segment distance - 선분 사이의 최단 거리
10. Half Plane Intersection(반평면 교집합)
11. tangent of convex hull(볼록다각형 외부의 한 점에서 볼록다각형으로 그린 접선)
    


# 알아둬야 할 것 #
1. N개의 점 집합이 주어졌을 때, 가장 먼 두 점은 convex hull위에 있고, 물론, 여기 있는 ConvexHull_CCW.cpp, Rotating_Calipers.cpp가 2개의 점(직선을 이루는 경우) 에 대해서는 처리를 잘 하지만, 중복 점 입력이 가능하고, 만약 모든 점이 동일한 좌표를 가지고 있다면, 이때의 convex hull은 그 점 자신이며, 가장 먼 두 점 사이의 거리는 0이다. -> Rotating_Calipers.cpp의 main 함수를 살펴 보자. 
2. 볼록다각형에 점이 포함되는지 아닌지 -> convexhull이 일직선인 경우, (convexhull.size() == 2) -> convexhull을 이루는 선분 위에 점이 있다면, 그 점은 convexhull에 포함되는 거다.
3. 반평면 교집합에서, 볼록 다각형의 내접원의 반지름, 중심을 구하는 법은, 볼록 다각형을 이루는 모든 변들을, 내부로 동일한 속도로 이동시키다 보면, 언젠가 HPI를 구할 수 없는(HPI가 false를 리턴하는)순간이 나오는데, 그 순간이, 내접원을 구한 순간이다. 선분을 내부로 이동시키는 방법은, 선분에 수직한 벡터를 이용하면 된다.HPI.cpp의 moveLineInside 함수 참고. 
    3-1) 각 변이 내부로 이동하는 거리를 d라고 하자. 
    3-2) 이분 탐색으로, HPI가 true->false를 리턴하는 순간의 d를 구한다. 
    3-3) 구해낸 d는, 볼록 다각형의 내접원의 반지름이다.
