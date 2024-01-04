사용 알고리즘 : fenwick Tree.

link : https://www.acmicpc.net/problem/2268

처음에 내가 fenwick tree 코드 자체에 문제가 있나 생각했었지만, 그것은 나의 바보같은 생각이었다.. 

fenwick tree의 update연산시, 그냥 초기화에 사용한 배열을 쓰고, 변화된 배열은 전혀 추적하지 않았다.. 멍청한 녀석.. 그럼 당연히 val이 diff값이 되어 틀릴 수밖에 없지..

기억하자. 항상 fenwick tree 사용 시에는, **변화된 배열을 추적하고, update 연산에 사용되는 diff값 계산시 변화된 배열을 이용해야 한다.**

아 이상한데서 헤메고있었네.. 

코드는 468ms, 17652kb 에 AC를 받는다. 

제출 기록 : https://www.acmicpc.net/status?from_mine=1&problem_id=2268&user_id=dlrkddnr2718


