// boj 10999 구간 합 구하기 2
// Lazy Propagation(recursion)
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
        // lazy 배열의 값이 0이 아닌 경우, 업데이트를 해야 할 필요성이 있다.
        if (lazy[node] != 0) { 
            // 어차피 leaf node 까지 내려가면, node가 관장하는 부분의 값을 lazy 배열의 값만큼 일괄적으로 업데이트해야 하므로, 구간의 길이만큼 업데이트 한다. 
            tree[node] += (end - start + 1) * lazy[node];
            // leaf node가 아닌 경우, 자식 노드들에게 재귀적으로 lazy 값을 전파한다. 
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
        ll num; cin >> num;
        segTree.update_range(i, i, num);
    }

    for (int i = 0; i < M + K; i++) {
        int a; cin >> a;
        if (a == 1) {
            int b, c; ll d; cin >> b >> c >> d;
            segTree.update_range(b-1, c-1, d);
        } else {
            int b, c; cin >> b >> c;
            cout << segTree.sum(b-1, c-1) << "\n";
        }
    }

    return 0;
}
