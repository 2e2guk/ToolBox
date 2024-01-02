사용 알고리즘 : Segment Tree

link : https://www.acmicpc.net/problem/2268

AC : 776ms, 34060kb

겉보기에는 그냥 간단한 Segment tree 문제 같지만, 문제를 자세히 읽지 않으면 틀리기 좋다. 나도 그랬다.. 

문제의 조건을 읽어보면, **i > j일 경우**에는 A[j] + A[j+1] + ... + A[i] 라고 나와 있다. 그런데, 모든 입력이 i < j 로 주어지진 않겠지? 

그래서, **i, j를 입력받고, i > j 이면, swap(i, j) 를 통해서, left에는 항상 더 작은 인덱스, right에는 항상 더 큰 인덱스를 전달**해 주면 된다. 

이거 때문에 맞왜틀을 좀 했던 문제다, 다행히 문제를 빨리 발견하긴 했지만..

정답 코드는, 776ms에 AC를 받는다. 펜윅 트리를 사용하면 더 빨라지겠지? https://www.acmicpc.net/status?from_mine=1&problem_id=2268&user_id=dlrkddnr2718
