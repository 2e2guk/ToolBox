# 최대 유량 알고리즘 정리
1. Ford-fulkerson
2. Edmonds-karp
3. Dinic -> 최소 컷, 포화된 간선들 구하는 함수들까지 포함. (<-boj 25365 test. AC)
4. Push-Relabel(naive)
5. Push-Relabel(FIFO queue opt)
6. Push-Relabel(HLPP opt)
7. MPM(Malhotra, Pramodh-Kumar and Maheshwari) algorithm
8. LR maxflow
9. Circulation

# 실행속도 비교
문제 : https://www.acmicpc.net/problem/12936
1. Dinic : 11576kb, 72ms
2. naive Push-Relabel : 4% TLE
3. FIFO queue + Push-Realabel : 14908kb, 104ms
4. MPM : 4% TLE
5. HLPP + Push-Ralbel : 4% TLE

# WorkFlow #
1. (231205) MPM, HLPP -> 각각 12936 문제에서 TLE, MLE를 받았기에, 코드를 좀 더 만져야 한다. -> HLPP가, capacity, flow배열을 유지하기에 MLE 발생, 그래서 Edge 구조체에서 직접 용량, 유량을 관리하도록 변경. 4% TLE. 
