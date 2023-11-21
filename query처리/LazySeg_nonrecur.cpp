// lazyseg 비재귀 구현
// https://www.acmicpc.net/blog/view/117 참고
/*
1. NodeType : node의 자료형.
2. LazyType : lazy값의 자료형.
3. F_Merge : (NodeType, NodeType)을 매개변수로 받아서 NodeType을 반환하는 Functor. 두 노드를 합치는 연산을 수행.
4. F_Update : (LazyType, NodeType)을 매개변수로 받아서 NodeType을 반환하는 Functor. 노드에 lazy값을 적용하는 연산을 수행.
5. F_Composition : (LazyType, LazyType)을 매개변수로 받아서 LazyType을 반환하는 Functor. lazy값 위에 lazy값을 적용하는 연산을 수행.

F_Merge는 결합법칙을 만족해야 하고, F_Update는 F_Merge와 분배법칙을 만족해야 합니다.
*/
// main 함수 사용 예시는 boj 10999
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename NodeType, 
         typename LazyType,
         typename F_Merge,
         typename F_Update,
         typename F_Composition>
struct LazySegTree { // 1-indexed
public:
    using A = NodeType;
    using B = LazyType;
    LazySegTree() : LazySegTree(0, A(), B()) {}
    explicit LazySegTree(int n, const A& e, const B& id)
        : n(n), e(e), id(id), lg(Log2(n)), sz(1 << lg), tree(sz << 1, e), lazy(sz, id) {}
    void Set(int i, const A& val) { tree[--i | sz] = val; }
    void Init() { for (int i = sz - 1; i; i--) Pull(i); }
    void Update(int i, const B& f) {
        --i |= sz;
        for (int j = lg; j; j--) Push(i >> j);
        Apply(i, f);
        for (int j = 1; j <= lg; j++) Pull(i >> j);
    }
    void Update(int l, int r, const B& f) {
        --l |= sz, --r |= sz;
        for(int i = lg; i; i--) {
            if (l >> i << i != l) Push(l >> i);
            if (r + 1 >> i << i != r + 1) Push(r >> i);
        }
        for(int L = l, R = r; L <= R; L >>= 1, R >>= 1) {
            if (L & 1) Apply(L++, f);
            if (~R & 1) Apply(R--, f);
        }
        for(int i = 1; i <= lg; i++) {
            if (l >> i << i != l) Pull(l >> i);
            if (r + 1 >> i << i != r + 1) Pull(r >> i);
        }
    }
    A Query(int i) {
        --i |= sz;
        for (int j = lg; j; j--) Push(i >> j);
        return tree[i];
    }
    A Query(int l, int r) {
        A L = e, R = e; --l |= sz, --r |= sz;
        for (int i = lg; i; i--) {
            if (l >> i << i != l) Push(l >> i);
            if (r + 1 >> i << i != r + 1) Push(r >> i);
        }
        for (; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) L = M(L, tree[l++]);
            if (~r & 1) R = M(tree[r--], R);
        }
        return M(L, R);
    }
private:
    const int n, lg, sz; const A e; const B id;
    vector<A> tree; vector<B> lazy;
    F_Merge M; F_Update U; F_Composition C;
    static int Log2(int n) {
        int ret = 0;
        while (n > 1 << ret) ret++;
        return ret;
    }
    void Apply(int i, const B& f) {
        tree[i] = U(f, tree[i]);
        if (i < sz) lazy[i] = C(f, lazy[i]);
    }
    void Push(int i) {
        Apply(i << 1, lazy[i]);
        Apply(i << 1 | 1, lazy[i]);
        lazy[i] = id;
    }
    void Pull(int i) {
        tree[i] = M(tree[i << 1], tree[i << 1 | 1]);
    }
};

//  NodeType, LazyType, F_Merge, F_Update, F_Composition는 문제별로 적절히 구현해야 한다. 
struct NodeType {
	long long val; int sz;
	constexpr NodeType(long long val, int sz) : val(val), sz(sz) {}
};

constexpr NodeType e(0, 0);

using LazyType = ll;

constexpr LazyType id = 0;

struct F_Merge {
	NodeType operator() (const NodeType& a, const NodeType& b) const {
		return NodeType(a.val + b.val, a.sz + b.sz);
	}
};

struct F_Update {
	NodeType operator() (const LazyType& a, const NodeType& b) const {
		return NodeType(b.val + a * b.sz, b.sz);
	}
};

struct F_Composition {
	LazyType operator() (const LazyType& a, const LazyType& b) const {
		return a + b;
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int n, m, k; cin >> n >> m >> k;
	LazySegTree<NodeType, LazyType, F_Merge, F_Update, F_Composition> ST(n, e, id);
	for (int i = 1; i <= n; i++) {
		ll t; cin >> t;
		ST.Set(i, NodeType(t, 1));
	}
	ST.Init();
	while (m + k--) {
		int t, l, r; LazyType f; cin >> t >> l >> r;
		if (t & 1) cin >> f, ST.Update(l, r, f);
		else cout << ST.Query(l, r).val << '\n';
	}
    return 0;
}
/*
1. F_Merge  = F_Merge는 결합법칙을 만족하고 항등원이 존재해야 합니다. 항등원은 존재한다면 그냥 사용하면 되고, 
만약 존재하지 않는다면 임의로 항등원을 정의해주면 됩니다
(특정 값을 항등원으로 이용하면서 F_Merge에서 a가 항등원이면 항상 b를 반환하고, b가 항등원이면 항상 a를 반환하도록 하면 됩니다). 
구간 합 구하기 2를 예로 들면 F_Merge(a, b)를 (a.val + b.val, a.sz + b.sz)로 정의하면 결합법칙을 만족하고, 항등원은 (0, 0)입니다.

F_Update = F_Update는 F_Merge와 교환법칙을 만족하고 항등함수가 존재해야 합니다. 
교환법칙에서 실수할 여지가 많으니 예시를 보면서 주의사항을 알아보겠습니다. 
구간 합 구하기 2는 F_Merge는 값의 덧셈을 이용하고, F_Update는 구간에 t를 더하는 연산을 구현해야 합니다. 
이때, [1, 2] 구간에 3을 더하는 경우는 (1 + 2) + 3 != (1 + 3) + (2 + 3)이므로 교환법칙이 성립하지 않습니다. 
이 문제는 NodeType에 (val, sz)를 저장하며 구간의 합과 구간의 길이를 관리하고, 
F_Update에서 (val, sz) 구간에 t를 더하는 연산을 (val + t * sz, sz)을 반환하도록 하면 해결됩니다. 
결합법칙이 성립하는 이유에 대한 설명은 연습으로 남깁니다. 
항등함수는 F_Update를 적용해도 NodeType값이 바뀌지 않도록 하는 LazyType이고,
이 정의에서는 t = 0이 항등함수가 됩니다. 만약 항등함수가 존재하지 않는다면 임의로 항등함수를 정의해주면 됩니다.

F_Composition = F_Composition은 lazy값이 있는 노드 위에 새로 LazyType을 덮어씌울 때 사용합니다. 
예를 들어 수열과 쿼리 13에선 LazyType(a, b)가 n -> a * n + b 연산으로 정의됩니다. 
여기서 F_Composition(L1, L2)는 n에 L2, L1 연산을 차례로 적용시키면 n -> L2.a * n + L2.b -> L1.a * (L2.a * n + L2.b) + L1.b이므로
 LazyType(L1.a * L2.a, L1.a * L2.b + L1.b)를 반환합니다. 구현은 함수의 합성을 생각하면서 처리하면 됩니다.
*/
