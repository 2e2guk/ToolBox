// Li-Chao Tree
// 직선 삭제 쿼리가 없는 convex hull trick을, Online으로 해결하는 자료구조. 
// main 함수 사용 예시는 boj 12795
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
struct Line {
    T a, b;
    T get(T x) const {
        return a * x + b;
    }
};

template<typename T>
struct Node {
    int l, r; // 자식 노드의 인덱스
    T s, e; // 구간의 시작과 끝
    Line<T> line;
};

template<typename T>
struct LiChaoTree {
    vector<Node<T>> tree;

    void init(T s, T e) {
        tree.push_back({-1, -1, s, e, {0, numeric_limits<T>::min()}});
    }

    void update(int node, Line<T> newLine) {
        T s = tree[node].s, e = tree[node].e;
        T m = (s + e) >> 1;

        Line<T> low = tree[node].line, high = newLine;
        if (low.get(s) > high.get(s)) swap(low, high);

        if (low.get(e) <= high.get(e)) {
            tree[node].line = high;
            return;
        }

        if (low.get(m) < high.get(m)) {
            tree[node].line = high;
            if (tree[node].r == -1) {
                tree[node].r = tree.size();
                tree.push_back({-1, -1, m + 1, e, {0, numeric_limits<T>::min()}});
            }
            update(tree[node].r, low);
        } else {
            tree[node].line = low;
            if (tree[node].l == -1) {
                tree[node].l = tree.size();
                tree.push_back({-1, -1, s, m, {0, numeric_limits<T>::min()}});
            }
            update(tree[node].l, high);
        }
    }

    T query(int node, T x) const {
        if (node == -1) return numeric_limits<T>::min();
        T s = tree[node].s, e = tree[node].e;
        T m = (s + e) >> 1;
        if (x <= m) return max(tree[node].line.get(x), query(tree[node].l, x));
        else return max(tree[node].line.get(x), query(tree[node].r, x));
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int q; cin >> q;
    LiChaoTree<ll> lichao;
    lichao.init(-2e12, 2e12);
    while (q--) {
        ll op, a, b; cin >> op;
        if (op == 1) {
            cin >> a >> b;
            lichao.update(0, {a, b});
        } else {
            cin >> a;
            cout << lichao.query(0, a) << "\n";
        }
    }
    return 0;
}
