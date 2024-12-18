boj 15504 프로그래밍 대결 : https://www.acmicpc.net/problem/15504

사용 알고리즘 : MCMF

지금까지 여러 개의 MCMF모델링을 했지만, 이 문제만큼 기가 막히는 문제를 본적이 없다. 모델링하는 과정이 아주 흥미로운, 아주 좋은 진짜 개좋은 MCMF문제이다. 

일단, 각 변수에 대해 정의를 다시 한번 살펴보자. 

A[i] = i번 참가자의 실력

H[i] = i번 참가자가 대회를 한 번 했을 때 느끼는 피로도

L[i] = i번 참가자의 최대 가능 대결 횟수

대회의 재미 - (대결의 흥미로움의 합) - (피로도의 합)

여기서 약간의 생각을 하면, 실력이 가장 좋은 사람(들)은 당연히 한 번도 지지 않을 것이다. 그리고 나머지 사람들은, 어찌 되었던 간에, 최소 한 번 은 저야 한다. 그러면, 실력이 최고가 아닌 사람

이 이길 수 있는 최대 횟수는, Li - 1회가 된다. 

그리고 이는 역으로 생각하면, 실력이 가장 좋은 사람(들) 은 최대 0회 질 수 있고, 나머지 사람들은 최대 1회 질 수 있다. 

이 문제의 목적은 대회의 재미를 최대화하는 것이다. 그러면, 여기서 모델링의 아이디어를 얻을 수 있다. 

소스 - 승리 - 패배 - 싱크

로 모델링하고, 간선을 다음과 같이 추가한다. 

소스 - 승리 : 

case 1) 최고의 실력을 가진 경우

-> 용량 : Li(한 번도 질 수 없으므로), 비용 : Hi

case 2) 그 외의 경우

-> 용량 : Li - 1(한 번은 어찌 되었든 간에 저야 한다), 비용 : Hi

case 1,2를 정리하면, 

용량은 현재 연결하려는 정점에 대응되는 사람이 최대 이길 수 있는 횟수, 비용은 해당 사람의 피로도

승리 - 패배 :

연결하는 경우는, 승리 정점에 해당되는 사람의 실력이, 패배 정점에 해당하는 사람의 실력보다 클 때이다. 

용량 : 1, 비용 : -(A[i] ^ A[j]) 로 연결한다, 이때, (A[i] > A[j]이고, i는 승리 정점집합의 원소, A[j]는 패비 정점의 원소이다)

패배 - 싱크 : 

case 1) 최고의 실력을 가진 경우

-> 용량 : 0, 비용 : Hi

case 2) 그 외의 경우

-> 용량 : 1, 비용 : Hi

case 1,2를 정리하면, 

용량은 현재 연결하려는 정점에 대응되는 사람이 최소 질 수 있는 횟수, 비용은 해당 사람의 피로도

그런데, 사실 문제 모델링의 하이라이트는, 각 간선 연결에서, **비용 값의 부호를 설정**하는 부분이라고 생각한다. 

우리의 목적은, 대회의 재미 를 최대화하는 것이다. 그러면, 대회의 재미 = (각 대결의 흥미로움의 합) - (피로도의 총합)이다. 

그러면, 대회의 재미를 최대화하려면, (각 대결의 흥미로움의 합)은 최대화하고, (피로도의 총합)은 최소화해야 한다. 

그러면, 그 과정을, 다음과 같이 처리하면 된다. 

피로도를 비용으로 줄 때는 양의 부호를, 대결의 흥미로움을 비용으로 줄 때는 -를 붙여서 부여한 후, MCMF를 돌리고, 결과값에 음수를 붙여서 출력하면 된다.

제출 코드는, 232ms에 AC를 받는다. 

https://www.acmicpc.net/status?from_mine=1&problem_id=15504&user_id=dlrkddnr2718
