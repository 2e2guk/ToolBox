// boj 4008 특공대
// cht
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename ValueType>
struct Line {
    ValueType slope, intercept;
    double xLeft;

    Line(ValueType _slope, ValueType _intercept) : slope(_slope), intercept(_intercept), xLeft(-1e18) {}

    ValueType getY(ValueType x) const {
        return slope * x + intercept;
    }

    double intersectX(const Line& other) const {
        return (double)(other.intercept - intercept) / (slope - other.slope);
    }
};

template<typename ValueType>
struct CHT {
    vector<Line<ValueType>> hull;

    void addLine(ValueType slope, ValueType intercept) {
        Line newLine(slope, intercept);
        while (!hull.empty()) {
            newLine.xLeft = newLine.intersectX(hull.back());
            if (hull.back().xLeft < newLine.xLeft)
                break;
            hull.pop_back();
        }
        hull.push_back(newLine);
    }

    ValueType query(ValueType x) {
        int l = 0, r = hull.size() - 1, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (hull[mid].xLeft <= x) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return hull[ans].getY(x);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, a, b, c; cin >> N >> a >> b >> c;
    vector<ll> x(N + 1, 0), dp(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> x[i];
        x[i] += x[i - 1];
    }

    CHT<ll> cht;
    cht.addLine(0, 0);

    for (int i = 1; i <= N; ++i) {
        dp[i] = cht.query(x[i]) + 1ll * a * x[i] * x[i] + 1ll * b * x[i] + c;
        cht.addLine(-2 * a * x[i], dp[i] + a * x[i] * x[i] - b * x[i]);
    }

    cout << dp[N] << '\n';
    return 0;
}
