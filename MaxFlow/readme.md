# 최대 유량 알고리즘 정리
1. Ford-fulkerson
2. Edmonds-karp
3. Dinic Maxflow
4. Push-Relabel(naive)
5. Push-Relabel(FIFO queue opt)
6. Push-Relabel(HLPP opt)
7. MPM(Malhotra, Pramodh-Kumar and Maheshwari) algorithm
8. Circulation + LR maxflow
9. Gomory-Hu Tree(all vertex pair max flow)

# 유의할 점 #
1. DinicMaxFlow.cpp 사용시, dinic 자체의 최대유량 구하는 함수랑, getMincut 함수 내의 최대 유량을 구하는 함수에 주의하자. 당연히, 최대 유량을 구하고, 디닉을 또 돌리면 두번째 디닉 수행의 결과는 당연히 0이다. 


# 실행속도 비교
문제 : https://www.acmicpc.net/problem/12936
1. Dinic : 11576kb, 72ms
2. naive Push-Relabel : 4% TLE
3. FIFO queue + Push-Realabel : 14908kb, 104ms
4. MPM : 4% TLE
5. HLPP + Push-Ralbel : 4% TLE

# WorkFlow #
0. (??) : Dinic -> 최소 컷, 포화된 간선들 구하는 함수들까지 포함. (<-boj 25365 test. AC)
1. (231205) MPM, HLPP -> 각각 12936 문제에서 TLE, MLE를 받았기에, 코드를 좀 더 만져야 한다. -> HLPP가, capacity, flow배열을 유지하기에 MLE 발생, 그래서 Edge 구조체에서 직접 용량, 유량을 관리하도록 변경. 4% TLE.
2. (231211) Circulation + LR maxflow 코드 작성중... main함수 작성하고 테스트하는거만 남았다.
3. (231212) Dinic 각 간선별로 흐르는 유량 출력부분 작성중... 일단 내가 만든 TC는 통과, 문제로 테스트해 볼 수 있으면 좋을 터인디.. -> vscode 0codetester.cpp 에서 작업중.
4. (231215) 2, 3번 전부, boj 25927 parity constriant maximum flow 문제를 해결하며 해결되었다. 업데이트도 완료.
