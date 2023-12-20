사용 알고리즘 : Stoer-Wagner Golbal Min-Cut

AC : 784ms AC : https://www.acmicpc.net/status?from_mine=1&problem_id=13367&user_id=dlrkddnr2718

문제는, 음 아닌 가중치가 부여된 undirected graph와, 간선을 끊는데 필요한 "effort"가 주어지는데, 이 effort가 간선에 부여된 가중치이다. 그러면, effort를 최소로, 그래프를 2개의 그룹으로 나누려면 어떻게 해야 하는가.. 이때 사용되는 것이 Stoer-Wagner 알고리즘(https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm)이다.

이 문제는 그냥 Stoer-Wagner 연습 문제이다. 

주의할 점은, 최대 유량 최소 컷 정리에 따라, stoer-wagner 알고리즘으로 얻어지는 global Min-Cut이, 이 그래프에서 소스와 정점 쌍을 잘 골라서 흘릴 수 있는 최대 유량 아닌가? 라고 생각할 수 있는데, 애초에 maxflow를 논의하는 상황이 "directed graph" 이기도 하고, 그에 따라서, 최대 유량 최소 컷 정리도, undirected graph에서는 성립하지 않는다.. 라고 결론내릴 수 있다. 
Stoer-Wagner 알고리즘은, 그래프의 연결성(간선의 가중치) 가 가장 작은 부분을 끊어서, 그래프를 두 그룹으로 나눈다. 
