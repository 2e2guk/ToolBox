# 쿼리를 처리하는 알고리즘/자료구조 #
1. segment tree(재귀, 비재귀) -> https://www.acmicpc.net/blog/view/117 참고. 
2. segment tree lazy propagation
3. fenwick tree 
4. merge sort tree
5. HLD
6. centriod decomposition
7. sqrt decomposition
8. Euler-Tour-Technique(ETT)
9. Dymanic Segment Tree
10. Persistant Segment Tree

# Query 처리 #
앵간하면 fenwick으로 하자. 이거 쓰면 seg, lazyseg 이런거 필요 없음 

# WorkFlow #
(**240103**) ETT.cpp 템플릿화, 업로드

(**240102**)fenwick 코드 수정할 필요가 있어보임. template<typename ValueType, typename IndexType> 두 개 이용하는 버전으로 수정. <- boj 2268fenw.cpp 에서 작업

(**240104**) 멍청한 녀석.. 틀린건 코드가 아니라 너였다.. https://github.com/2e2guk/ToolBox/tree/main/query%EC%B2%98%EB%A6%AC/problems/2268fenw 참고.. 코드엔 이상 없다. 의심해서 미안해

(**240330**) LazyProp(재귀) 코드 구현

(**240331**) Dynamic Segment Tree, Merge-Sort Tree 구현

