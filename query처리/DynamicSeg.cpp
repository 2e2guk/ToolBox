// Dynamic Segment Tree
// pointer 
// main 함수 예시는 boj 2042
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename ValueType, typename IndexType>
class DynamicSegmentTree {
public:
    struct Node {
        ValueType value = ValueType();
        Node *left = nullptr, *right = nullptr;
    };

private:
    Node *root = new Node();

    void update(Node *node, IndexType nodeLeft, IndexType nodeRight, IndexType updateIndex, ValueType value) {
        if(updateIndex < nodeLeft || updateIndex > nodeRight) return;
        if(nodeLeft == nodeRight) {
            node->value = value;
            return;
        }
        IndexType mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if(updateIndex <= mid) {
            if(!node->left) node->left = new Node();
            update(node->left, nodeLeft, mid, updateIndex, value);
        } else {
            if(!node->right) node->right = new Node();
            update(node->right, mid + 1, nodeRight, updateIndex, value);
        }
        node->value = (node->left ? node->left->value : ValueType()) + (node->right ? node->right->value : ValueType());
    }

    ValueType query(Node *node, IndexType nodeLeft, IndexType nodeRight, IndexType queryLeft, IndexType queryRight) {
        if(!node || nodeRight < queryLeft || nodeLeft > queryRight) return ValueType();
        if(nodeLeft >= queryLeft && nodeRight <= queryRight) return node->value;
        IndexType mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        return query(node->left, nodeLeft, mid, queryLeft, queryRight) + query(node->right, mid + 1, nodeRight, queryLeft, queryRight);
    }

public:
    void update(IndexType index, ValueType value) {
        update(root, (IndexType)0, numeric_limits<IndexType>::max(), index, value);
    }

    ValueType query(IndexType left, IndexType right) {
        return query(root, (IndexType)0, numeric_limits<IndexType>::max(), left, right);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    DynamicSegmentTree<ll, ll> dynaseg;
    for(int i = 0; i < n; i++) {
        ll v; cin >> v;
        dynaseg.update(i * 5, v);
    }
    for(int i = 0; i < m + k; i++) {
        int op; cin >> op;
        if(op == 1) {
            ll b, c; cin >> b >> c; b--;
            dynaseg.update(b * 5, c);
        }
        if(op == 2) {
            ll b, c; cin >> b >> c; b--; c--;
            cout << dynaseg.query(b * 5, c * 5) << "\n";
        }
    }
    return 0;
}
