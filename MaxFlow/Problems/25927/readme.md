사용 알고리즘 : Dinic, circulation with demands and lower bounds(LR flow)

일단,, 이 문제 해결을 위해 약 2~3일은 쓴 것 같다. 
일단, 문제를 간단히 요약해 보겠다. 기존 maxflow문제처럼, 간선에 용량이 주어진다. 그런데 추가적인 제약 조건인, parity constraint가 존재하는데, 설명은 수식이 들어가 어렵지만, 정리하면 다음과 같다. 

1. p[i] = 0인 간선 (u[i], v[i]) =  이 간선에는, 짝수 유량이 흘러야 한다. 이후의 설명에서 이걸, even edge 라고 부르겠다. <- even constraint
2. p[i] = 1인 간선 (u[i], v[i]) = 이 간선에는 홀수 유량이 흘러야 한다. 이후의 설명에서 이걸 odd edge라고 부르겠다. <- odd constraint

그리고, 주어진 parity coinstraint를 만족시키는, 최대 유량을 찾는 문제이다. 
일단, 처음에는, 예제 입력들의 flow network를 모델링하고, 유량을 추적하다가, 혹시 이거 odd edge로만 혹은 even edge로만 이루어진 증가 경로를 통해서 유량을 증가시킬 수 있는게 아닐까? 라고 생각했었다. 머지 않아 그 생각은 잘못된 것임을 깨달았는데, odd + odd = even 이므로, even edge로만 증가 경로가 구성되다가, odd edge 2개로 쪼개져도 된다는 뜻이므로, 처음의 나의 생각이 틀렸다는 것을 알 수 있었다. 

그런데, 이 아이디에 착안해 힌트를 얻었는데, 간단한 circulation 모델링의 예를 들어 보자. 

u -> v 로 [l, r] flow constraint가 부여되어 있다면, demand[u] += l, demand[v] -= l 이다. 그리고, 기존의 이 간선의 용량은, r에서 r-l로 바뀐다. 

일단, even constriant를 처리하는 것은 간단하다, "짝수" 의 유량이 흘러야 하므로, 간선의 용량을 현재 간선의 용량(짝수일수도, 홀수일수도 있다)보다 작은, 가장 큰 짝수로 설정하면 된다. 이걸 떠올리는 것은 그렇게까지 어렵지 않다. 
odd constraint를 처리하는 것은, "홀수"의 유량이 흘러야 하므로, "(짝수) + 1" 로 찢는 생각을 해 볼 수 있다. 일단 강제로 유량 1의 전송을 시도한다. 그리고, circulation 문제의 모델링이 그러하듯, 이 간선의 유량은 (capacity) - 1 이 될 것이다. 
