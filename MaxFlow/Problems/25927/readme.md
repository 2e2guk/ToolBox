사용 알고리즘 : Dinic, circulation with demands and lower bounds(LR flow)
문제 링크 : https://www.acmicpc.net/problem/25927

일단,, 이 문제 해결을 위해 약 2~3일은 쓴 것 같다. 
일단, 문제를 간단히 요약해 보겠다. 기존 maxflow문제처럼, 간선에 용량이 주어진다. 그런데 추가적인 제약 조건인, parity constraint가 존재하는데, 설명은 수식이 들어가 어렵지만, 정리하면 다음과 같다. 

1. p[i] = 0인 간선 (u[i], v[i]) =  이 간선에는, 짝수 유량이 흘러야 한다. 이후의 설명에서 이걸, even edge 라고 부르겠다. <- even constraint
2. p[i] = 1인 간선 (u[i], v[i]) = 이 간선에는 홀수 유량이 흘러야 한다. 이후의 설명에서 이걸 odd edge라고 부르겠다. <- odd constraint

그리고, 주어진 parity coinstraint를 만족시키는, 최대 유량을 찾는 문제이다. 
일단, 처음에는, 예제 입력들의 flow network를 모델링하고, 유량을 추적하다가, 혹시 이거 odd edge로만 혹은 even edge로만 이루어진 증가 경로를 통해서 유량을 증가시킬 수 있는게 아닐까? 라고 생각했었다. 머지 않아 그 생각은 잘못된 것임을 깨달았는데, odd + odd = even 이므로, even edge로만 증가 경로가 구성되다가, odd edge 2개로 쪼개져도 된다는 뜻이므로, 처음의 나의 생각이 틀렸다는 것을 알 수 있었다. 

그런데, 이 아이디에 착안해 힌트를 얻었는데, 간단한 circulation 모델링의 예를 들어 보자. 

u -> v 로 [l, r] flow constraint가 부여되어 있다면, demand[u] += l, demand[v] -= l 이다. 그리고, 기존의 이 간선의 용량은, r에서 r-l로 바뀐다. 

일단, even constriant를 처리하는 것은 간단하다, "짝수" 의 유량이 흘러야 하므로, 간선의 용량을 현재 간선의 용량(짝수일수도, 홀수일수도 있다)보다 작은, 가장 큰 짝수로 설정하면 된다. 이걸 떠올리는 것은 그렇게까지 어렵지 않다. 
odd constraint를 처리하는 것은, "홀수"의 유량이 흘러야 하므로, "(짝수) + 1" 로 찢는 생각을 해 볼 수 있다. 일단 강제로 유량 1의 전송을 시도한다. 그리고, circulation 문제의 모델링이 그러하듯, 이 간선의 유량은 (capacity) - 1 이 될 것이다. 그리고, 이 odd edge를, even edge로 강제로 바꾼다. 하는 법은, (capacity) - 1 이 짝수라면, 이 값을 용량으로 부여, 홀수라면 (capacity) - 2를 용량으로 부여한다. 

이렇게 모델링하고, 과연 정점의 demand값이 무엇을 의미할지 생각해 보자. 만약, feasible한 flow가 흐른다면, ns에서 나가는 간선, nt로 들어가는 간선들은 모두 포화된다. 그리고 이 간선들의 용량은 모두 1이다. 
그러면, demand값은, "그 정점으로 흘러들어 가는 유량의 홀짝성" 을 의미하게 된다.

그러니까, 우리는 모든 그래프의 간선을 even edge로 바꿨고, 고로, demand의 홀짝성이 홀수인 정점이 존재한다면, 그냥 이건 불가능한 경우인 것이다. 왜냐하면, 홀수는 아무리 짝수의 합으로 나타내려고 해도 불가능하기 때문이다. 
물론, 소스, 싱크는 제외이다. 왜? 어차피 t -> s로의 무한 용량의 간선이 연결되어서, "demand의 홀짝성에 따른 불가능한 경우"의 의미가 없어진다.

여튼, 이렇게 모델링하고, 나머지는 그냥 circulation with edge demands and lower bounds 문제에서, 최대 유량을 찾는 과정을 하면 된다. 
주의할 점은, 만약 feasible한 flow가 흐르면, odd edge에는 1의 유량이 다 흐르고 있는 것이므로, odd edge의 유량에는, 1을 더해 줘야 한다. 우리는 그래프의 모든 간선을 even edge로 바꿨으므로, 간선에 흐르는 유량을 조회해 보면 짝수만 나온다. 

정답 코드는 120ms에 AC를 받는다. 14회의 제출기록,,, 진짜 인간승리다. 
https://www.acmicpc.net/status?from_mine=1&problem_id=25927&user_id=dlrkddnr2718
