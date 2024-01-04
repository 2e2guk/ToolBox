사용 알고리즘 : 밀러-라빈 소수판별법, 폴라드-로 고속 소인수분해 알고리즘, 오일러-피 함수(최적화된 버전)

link : https://www.acmicpc.net/problem/13926

오일러-피 함수(Euler-totient function, Euler-phi function, https://en.wikipedia.org/wiki/Euler%27s_totient_function)는, 

**phi(n) : 1~n 사시의 수 중, n과 서로소인 수의 개수를 의미한다.**

고로, 이 문제는 최적화된 오일러-피 함수를 작성하면 되는 문제이다. 

**서로소인** 소수 집합 P={p1, p2, ... , pi}, 양수 집합 A={a1, a2, ... , ai} 에 대해서, 임의의 양수 N은, **유일한 소인수분해 형태인**

N = p1^a1 * p2^a2 * ... * pi^ai 를 가짐이 알려져 있다. 

어떤 양수 n에 대해, 오일러-피 함수 phi(n)은, 

- PI(1 <= k <= i) pk^(ak-1)*(pk-1)  <- **n이 소수가 아닐 때**

- n-1  <- **n이 소수일 때**

의 값을 가진다. 

고로, 우리는 **소인수분해 결과, 빠른 소수 판별 알고리즘** 만 있다면, 최적화된 오일러-피 함수를 작성할 수 있음을 알 수 있다. 

고로, 빠른 소수 판별 알고리즘인 Miller-Rabin primality test, 

빠른 소인수분해 알고리즘인 Pollard-Rho 알고리즘으로, 최적화된 오일러-피 함수를 작성해 이 문제를 해결할 수 있다. 

정답 코드는, 100ms, 18068kb 에 AC를 받는다. 

제출 기록 : https://www.acmicpc.net/status?from_mine=1&problem_id=13926&user_id=dlrkddnr2718
