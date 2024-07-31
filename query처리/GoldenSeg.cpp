// ITMO pilot course segTree pt1, step2 #1
// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A
// boj 16993 연속합과 쿼리 도 참고하자. 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
template <typename ValueType, typename IndexType>
struct GoldenSeg {
    vector<ValueType> arr, pref, suff, ans, sum;
    ValueType n;
 
    GoldenSeg(const vector<ValueType>& input) {
        n = input.size();
        arr = input;
        pref = sum = ans = suff = vector<ValueType>(n * 4);
        build(1, 0, n - 1);
    }
 
    void build(IndexType i, IndexType tl, IndexType tr) {
        if (tl == tr) {
            suff[i] = ans[i] = pref[i] = max((ValueType)0, arr[tl]);
            sum[i] = arr[tl];
        } else {
            IndexType tm = (tl + tr) / 2;
            build(i * 2, tl, tm);
            build(i * 2 + 1, tm + 1, tr);
            ans[i] = max(ans[i * 2], max(ans[i * 2 + 1], suff[i * 2] + pref[i * 2 + 1]));
            pref[i] = max(pref[i * 2], sum[i * 2] + pref[i * 2 + 1]);
            suff[i] = max(suff[i * 2 + 1], sum[i * 2 + 1] + suff[i * 2]);
            sum[i] = sum[i * 2] + sum[i * 2 + 1];
        }
    }
 
    void update(IndexType i, IndexType tl, IndexType tr, IndexType p) {
        if (tl == tr) {
            suff[i] = ans[i] = pref[i] = max((ValueType)0, arr[tl]);
            sum[i] = arr[tl];
        } else {
            IndexType tm = (tl + tr) / 2;
            if (tm >= p) update(i * 2, tl, tm, p);
            else update(i * 2 + 1, tm + 1, tr, p);
            
            ans[i] = max(ans[i * 2], max(ans[i * 2 + 1], suff[i * 2] + pref[i * 2 + 1]));
            pref[i] = max(pref[i * 2], sum[i * 2] + pref[i * 2 + 1]);
            suff[i] = max(suff[i * 2 + 1], sum[i * 2 + 1] + suff[i * 2]);
            sum[i] = sum[i * 2] + sum[i * 2 + 1];
        }
    }
 
    void update(IndexType idx, ValueType val) {
        arr[idx] = val;
        update(1, 0, n - 1, idx);
    }
    struct Result {
        ValueType ans, pref, suff, sum;
    };
 
    Result merge(const Result &left, const Result &right) {
        Result res;
        res.ans = max({left.ans, right.ans, left.suff + right.pref});
        res.pref = max(left.pref, left.sum + right.pref);
        res.suff = max(right.suff, right.sum + left.suff);
        res.sum = left.sum + right.sum;
        return res;
    }
 
    Result query(IndexType i, IndexType tl, IndexType tr, IndexType l, IndexType r) {
        if (l > r) {
            return {numeric_limits<IndexType>::min(), numeric_limits<IndexType>::min(), numeric_limits<IndexType>::min(), 0};
        }
        if (tl == l && tr == r) {
            return {ans[i], pref[i], suff[i], sum[i]};
        }
        IndexType tm = (tl + tr) / 2;
        return merge(query(i * 2, tl, tm, l, min(r, tm)),
                     query(i * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }
    Result query(IndexType l, IndexType r) {
        return query(1, 0, n - 1, l, r);
    }
};
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll n, m; cin >> n >> m;
    vector<ll> input(n);
    for (auto &x : input) cin >> x;
 
    GoldenSeg<ll, int> segTree(input);
    cout << segTree.query(0, n - 1).ans << "\n";
 
    while (m--) {
        ll x, y; cin >> x >> y;
        segTree.update(x, y);
        cout << segTree.query(0, n - 1).ans << "\n";
    }
    return 0;
}
