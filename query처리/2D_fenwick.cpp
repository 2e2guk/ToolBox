// 2차원 펜윅 트리, X x Y 직사각형 영역 처리 가능.
// boj 11658 구간 합 구하기 3
#include <bits/stdc++.h>
using namespace std;

template<typename ValueType, typename IndexType>
class fenwick_2d {
public:
    IndexType Y, X;
    vector<vector<ValueType>> tree;
    fenwick_2d(IndexType Y, IndexType X) : Y(Y), X(X) {
        tree.resize(Y, vector<ValueType>(X));
    }
    void update(IndexType y, IndexType x, ValueType diff) {
        while (y <= Y) {
            IndexType _x = x;
            while (_x <= X) {
                tree[y][_x] += diff;
                _x += _x & -_x;
            }
            y += y & -y;
        }
    }
    ValueType sum(IndexType y, IndexType x) {
        if (y <= 0 || x <= 0) return 0;
        ValueType ret = 0;
        while (y) {
            IndexType _x = x;
            while (_x) {
                ret += tree[y][_x];
                _x -= _x & -_x;
            }
            y -= y & -y;
        }
        return ret;
    }
    ValueType query(IndexType y1, IndexType x1, IndexType y2, IndexType x2) {
        return sum(y2, x2) - sum(y1 - 1, x2) - sum(y2, x1 - 1) + sum(y1 - 1, x1 - 1);
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;

    vector<vector<int>> arr = vector<vector<int>>(n + 1, vector<int>(n + 1));
    fenwick_2d<int, int> fenw2d(n + 1, n + 1);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> arr[i][j];
            fenw2d.update(j, i, arr[i][j]);
        }
    }
    for (int i = 0; i < m; ++i) {
        int op, x1, y1; cin >> op >> x1 >> y1;

        if (op == 1) {
            int x2, y2; cin >> x2 >> y2;
            cout << fenw2d.query(y1, x1, y2, x2) << "\n";
        } else {
            int c; cin >> c;
            fenw2d.update(y1, x1, c - arr[x1][y1]);
            arr[x1][y1] = c;
        }
    }
    return 0;
}
