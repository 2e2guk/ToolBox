# (계산)기하 알고리즘 #
1. convex hull + CCW -> Graham's Scan
2. Rotating Calipers -> 점 집합에서 가장 먼 두 점은, convex hull 위에 있다.
3. PolygonArea - 다각형 면적 구하기. kahan's sumation 적용해 정밀도 향상.
4. Point in Convex Polygon - 볼록다각형 내의 점 판정.
5. PointOnLineSegment - 선분 위에 점이 있는지 확인.


# 알아둬야 할 것 #
1. N개의 점 집합이 주어졌을 때, 가장 먼 두 점은 convex hull위에 있고, 물론, 여기 있는 ConvexHull_CCW.cpp, Rotating_Calipers.cpp가 2개의 점(직선을 이루는 경우) 에 대해서는 처리를 잘 하지만, 중복 점 입력이 가능하고, 만약 모든 점이 동일한 좌표를 가지고 있다면, 이때의 convex hull은 그 점 자신이며, 가장 먼 두 점 사이의 거리는 0이다. -> Rotating_Calipers.cpp의 main 함수를 살펴 보자. 
2. 볼록다각형에 점이 포함되는지 아닌지 -> convexhull이 일직선인 경우, (convexhull.size() == 2) -> convexhull을 이루는 선분 위에 점이 있다면, 그 점은 convexhull에 포함되는 거다.
