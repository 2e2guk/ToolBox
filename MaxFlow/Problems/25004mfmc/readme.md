link = https://www.acmicpc.net/problem/25004

문제를 간단히 요약해 보자면, 다음과 같다. 미끼에는, 3가지 재료인 attractor, feed, poison 이 있고, 우리는 이를 적절히 조합해서 벌레를 잡기 위한 미끼를 만드는데, 이 미끼를 만드는데는 비용이 든다. 

우리는 total profit을 최대화해야 하고, **total profit = total price - total production cost** 이다. 

그리고, total production cost는, 하나의 미끼 안에 있는, 서로 다른 3가지 구성 요소(attractor, feed, poison)의 개수의 영향을 받는다. 

이 문제는 optimization problem으로써, 우리는 total production cost를 최소화하면, max total profit을 얻을 수 있다. 

그럼, 이를 flow network로 모델링함으로써 해결할 수 있다. 

Flow network modeling

**s - 가능한 미끼의 가짓수(256 * 3가지) - 벌레 - 싱크**

이렇게 모델링하면 된다. 그리고, 각 연결의 용량을 알아보자. 

주의할 점은, "0" 으로 주어진 값도 연결해 주어야 한다는 것인데, 이는 그냥 단순히, 가능한 모든 값을 연결하는 것이다. 어차피 우리는 최대 판매 이익을 np로 고정하므로, 차액은 알아서 빠진다.

1) s - 가능한 미끼의 가짓수
-> 이 경우, 1 ~ 256까지는 attractor, 256 + 1 ~ 256 + 256 까지는 feed, 이런 식으로, 3 * 256가지 가능한 case를 모두 연결한다.
그리고, 이때 각 간선의 용량은, ca, ck, ct 가 된다.

2) 가능한 미끼의 가짓수 - 벌레
-> 문제에서 입력으로 주어지는, a, k, t 값에 맞추어서, 해당 벌레에 해당하는 올바른 미끼와 연결해 주면 된다. 이때의 용량은, 무한대이다.

3) 벌레 - 싱크
-> 주어진 n마리의 벌레와, 싱크를 용량 p인 간선으로 연결한다.
이 용량을 p로 설정하는 이유는, 우리는 우리가 만든 미끼를 판매해사 얻을 수 있는 순수 이익이 p이다. 그런데, 곤충은 n마리, 그러면, 총 얻을 수 있는 최대 판매 이익은, np가 된다.
그러면, 이렇게 구성한 flow network에서 이 최대 판매 이익을 넘지 못하도록, 제한을 걸어 준 것이다. 

그럼, 이렇게 modeling 한 flow network가 무슨 의미를 가지냐? 이 flow로 구할 수 있는 것은, 최소 컷. 곧 이는, 최소 생산 비용을 의미한다. 고로, 이렇게 구성한 flow network에서
최대 유량을 구하면,그는 최소 생산 비용이 된다. 


우리가 구하고자 하는 값은, np - Maxflow 의 값이 된다. 

정답 코드는, 2868kb, 4ms에 AC를 받는다. 
https://www.acmicpc.net/status?from_mine=1&problem_id=25004&user_id=dlrkddnr2718
