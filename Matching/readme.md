# Matching #
1. dfs기반의 이분 매칭을 찾는 알고리즘
2. Hopcroft-karp
3. Gabow's general weighted maximum matching
4. Hungarian(kuhn-munkres) <- 할당 문제

# 알아두어야 할 것 #
1. Hopcroft-Karp : 이분 매칭을 구하는 hopcroft-karp 알고리즘은, Dinic's algorithm을 이분 그래프 환경으로 국한되게 만든 결과물이다.
  이분 매칭 환경에서, 간선의 용량은 unit capacity이므로, hopcroft-karp 알고리즘의 시간 복잡도는 O(sqrt(V) E) 가 된다...



# 성능 테스트 #
Hopcroft-Karp vs Dinic -> 애초에 hopcroft-karp가, 이분 그래프에서 dinic을 적용한 것이고, 시간 복잡도도 O(V^2E)(Dinic) -> O(sqrt(V)*E)(Hopcroft-Karp) 가 되어서, 
"이분 그래프" 로 제한하면, Hopcroft-karp가 Dinic 보다 빨라야 한다. 


문제 : https://www.acmicpc.net/problem/11376 에 대해,

1.Hopcroft-Karp = 10084kb, 132ms

2.Dinic = 34468kb, 156ms 

의 결과를 보여줬고, 고로, Hopcroft-karp의 구현이 타당함을 알수 있다.(근데 그럴수밖에 없다. 왜? 난 이거 구사과님 블로그로 배웠으니까.. 구현도 구사과님 구현과 매우 유사하다) -> ??????? 
