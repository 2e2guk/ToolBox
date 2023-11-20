// 비재귀 segtree, 1-based index
// 쿼리는 구간 합 쿼리 
/*
구현 코드를 사용하려면 문제 별로 적절히 NodeType, F_Merge를 구현해야 합니다.
1. NodeType = node의 자료형 
2. F_Merge는 결합법칙을 만족하고 항등원이 존재해야 합니다. 구간 합 구하기를 예로 들면 F_Merge(a, b)를 a + b를 반환하도록 정의하면 결합법칙을 만족하고, 항등원은 0이 됩니다.
*/
// https://www.acmicpc.net/blog/view/117 참고
// main 함수 사용 예시는 boj 2042 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename NodeType, typename F_Merge>
struct SegTree { // 1-indexed
public:
	SegTree() : SegTree(0, NodeType()) {}
	explicit SegTree(int n, const NodeType& e) : n(n), lg(Log2(n)), sz(1 << lg), e(e), tree(sz << 1, e) {}
	void Set(int i, const NodeType& val) { tree[--i | sz] = val; }
	void Init() { for (int i = sz - 1; i; i--) tree[i] = M(tree[i << 1], tree[i << 1 | 1]); }
    // update = i번 노드의 값을 val로 설정
	void Update(int i, const NodeType& val) {
		tree[--i |= sz] = val;
		while (i >>= 1) tree[i] = M(tree[i << 1], tree[i << 1 | 1]);
	}
	NodeType Query(int l, int r) const {
		NodeType L = e, R = e;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) L = M(L, tree[l++]);
			if (~r & 1) R = M(tree[r--], R);
		}
		return M(L, R);
	}
private:
	const int n, lg, sz; const NodeType e;
	vector<NodeType> tree;
	F_Merge M;
	static int Log2(int n) {
		int ret = 0;
		while (n > 1 << ret) ret++;
		return ret;
	}
};

// 자료형 적절히 수정
struct F_Merge {
	ll operator() (const ll& a, const ll& b) const {
		return a + b;
	}
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int n, m, k; cin >> n >> m >> k;
	SegTree<ll, F_Merge> ST(n, 0);
	for (int i = 1; i <= n; i++) {
		ll t; cin >> t;
		ST.Set(i, t);
	}
	ST.Init();
	while (m + k--) {
		ll t, a, b; cin >> t >> a >> b;
		if (t & 1) ST.Update(a, b);
		else cout << ST.Query(a, b) << '\n';
	}
    return 0;
}
