// Trenary search(삼분 탐색)
// 아래로 볼록, 혹은 위로 볼록(unimodal) 함 함수에 대해, 극값 혹은 최대/최소를 구하는 테크닉. 
// O(logN)
// main 함수 사용 예시는 boj 8986
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename ValueType>
class TernarySearch {
private:
    vector<ValueType> data;
    function<ValueType(int)> costFunction;

public:
    TernarySearch(const vector<ValueType>& data, function<ValueType(int)> costFunction)
        : data(data), costFunction(costFunction) {}

    ValueType FindMin() {
        ValueType lo = 0, hi = data.back();
        while (hi - lo >= 3) {
            ValueType p = (lo * 2 + hi) / 3, q = (lo + hi * 2) / 3;
            if (costFunction(p) <= costFunction(q)) hi = q;
            else lo = p;
        }

        ValueType result = numeric_limits<ValueType>::max();
        for (ValueType i = lo; i <= hi; ++i)
            result = min(costFunction(i), result);
        return result;
    }

    ValueType FindMax() {
        ValueType lo = 0, hi = data.back();
        while (hi - lo >= 3) {
            ValueType p = (lo * 2 + hi) / 3, q = (lo + hi * 2) / 3;
            if (costFunction(p) >= costFunction(q)) hi = q;
            else lo = p;
        }

        ValueType result = numeric_limits<ValueType>::min();
        for (ValueType i = lo; i <= hi; ++i)
            result = max(costFunction(i), result);
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    vector<ll> x(N);
    for (int i = 0; i < N; ++i)
        cin >> x[i];

    auto costFunction = [&](int dist) -> ll {
        ll totalCost = 0;
        for (int i = 1; i < x.size(); ++i)
            totalCost += abs(1LL * dist * i - x[i]);
        return totalCost;
    };

    TernarySearch<ll> search(x, costFunction);
    cout << search.FindMin();
    return 0;
}
