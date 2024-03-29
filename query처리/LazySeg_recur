// Lazy Propagation
// main 함수 예시는 boj 10999 구간 합 구하기 2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename ValueType, typename IndexType>
class Lazyprop {
private:
    vector<ValueType> tree;
    vector<ValueType> lazy;
    IndexType size;

    void update_lazy(IndexType node, IndexType start, IndexType end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update_range(IndexType node, IndexType start, IndexType end, IndexType left, IndexType right, ValueType diff) {
        update_lazy(node, start, end);
        if (left > end || right < start) return;
        if (left <= start && end <= right) {
            tree[node] += (end - start + 1) * diff;
            if (start != end) {
                lazy[node * 2] += diff;
                lazy[node * 2 + 1] += diff;
            }
            return;
        }
        IndexType mid = (start + end) / 2;
        update_range(node * 2, start, mid, left, right, diff);
        update_range(node * 2 + 1, mid + 1, end, left, right, diff);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ValueType sum(IndexType node, IndexType start, IndexType end, IndexType left, IndexType right) {
        update_lazy(node, start, end);
        if (left > end || right < start) return 0;
        if (left <= start && end <= right) return tree[node];
        IndexType mid = (start + end) / 2;
        return sum(node * 2, start, mid, left, right) + sum(node * 2 + 1, mid + 1, end, left, right);
    }

public:
    Lazyprop(int n) {
        IndexType h = (int)ceil(log2(n));
        size = 1 << (h + 1);
        tree.resize(size, 0);
        lazy.resize(size, 0);
    }

    ValueType sum(IndexType left, IndexType right) {
        return sum(1, 0, size/2 - 1, left, right);
    }

    void update_range(IndexType left, IndexType right, ValueType diff) {
        update_range(1, 0, size/2 - 1, left, right, diff);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    Lazyprop<ll, int> segTree(N);
    for (int i = 0; i < N; i++) {
        ll num;
        cin >> num;
        segTree.update_range(i, i, num);
    }

    for (int i = 0; i < M + K; i++) {
        int a;
        cin >> a;
        if (a == 1) {
            int b, c;
            ll d;
            cin >> b >> c >> d;
            segTree.update_range(b-1, c-1, d);
        } else {
            int b, c;
            cin >> b >> c;
            cout << segTree.sum(b-1, c-1) << "\n";
        }
    }

    return 0;
}
