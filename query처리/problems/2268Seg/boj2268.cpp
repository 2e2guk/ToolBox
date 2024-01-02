// boj 2268 수들의 합 7
// SegTree
// 쿼리개수 Q, O(QlogN)
// main 함수 사용예시는 boj 2042, 224ms AC
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename ValueType, typename IndexType>
struct Seg {
    vector<ValueType> segmentTree;
    vector<ValueType> array;
    IndexType n;

    Seg(const vector<ValueType>& inputArray) {
        n = inputArray.size();
        array = inputArray;
        IndexType treeDepth = ceil(log2(n));
        IndexType treeSize = 1 << (treeDepth + 1);
        segmentTree.resize(treeSize);
        makeSegmentTree(1, 0, n - 1);
    }

    ValueType makeSegmentTree(IndexType node, IndexType start, IndexType end) {
        if (start == end) {
            return segmentTree[node] = array[start];
        }
        IndexType mid = (start + end) / 2;
        return segmentTree[node] = makeSegmentTree(node * 2, start, mid) + makeSegmentTree(node * 2 + 1, mid + 1, end);
    }

    // 인덱스 idx의 값을, diff만큼 업데이트한다. 
    void updateSegmentTree(IndexType node, IndexType start, IndexType end, IndexType idx, ValueType diff) {
        if (idx < start || idx > end) return;
        segmentTree[node] += diff;
        if (start != end) {
            IndexType mid = (start + end) / 2;
            updateSegmentTree(node * 2, start, mid, idx, diff);
            updateSegmentTree(node * 2 + 1, mid + 1, end, idx, diff);
        }
    }

    ValueType sumSegmentTree(IndexType node, IndexType left, IndexType right, IndexType start, IndexType end) {
        if (left > end || right < start) return 0;
        if (left <= start && right >= end) return segmentTree[node];
        IndexType mid = (start + end) / 2;
        return sumSegmentTree(node * 2, left, right, start, mid) + sumSegmentTree(node * 2 + 1, left, right, mid + 1, end);
    }

    void update(IndexType idx, ValueType newValue) {
        ValueType diff = newValue - array[idx];
        array[idx] = newValue;
        updateSegmentTree(1, 0, n - 1, idx, diff);
    }

    ValueType query(IndexType left, IndexType right) {
        return sumSegmentTree(1, left, right, 0, n - 1);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<ll> arr(n, 0);
    Seg<ll, ll> segTree(arr);

    for (int i = 0; i < m; i++) {
        ll order, left, right;
        cin >> order >> left >> right;
        if (order == 1) {
            ll diff = right - arr[left - 1];
            segTree.update(left - 1, diff);
        } else {
            if(left > right) swap(left, right);
            cout << segTree.query(left - 1, right - 1) << '\n';
        }
    }
    return 0;
}
