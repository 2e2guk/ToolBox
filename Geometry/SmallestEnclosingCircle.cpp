// 최소 외접원
// O(N), worst O(N^3)
// main 함수 사용 예시는 boj 2626
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct p { double x, y; };

double eps = 1e-4;

double dis(p a, p b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

pair<double, p> SmallestEnclosingCircle(const vector<p>& v) {
    int N = v.size();
    p cen = {0, 0};
    double r = 0;

    for(int i = 0; i < N; i++) {
        if(dis(cen, v[i]) <= r) continue;

        cen = v[i], r = 0;

        for(int j = 0; j < i; j++) {
            if(dis(cen, v[j]) <= r) continue;

            cen = {(v[i].x + v[j].x) / 2, (v[i].y + v[j].y) / 2};
            r = dis(cen, v[i]);

            for(int k = 0; k < j; k++) {
                if(dis(cen, v[k]) <= r) continue;

                cen.x = ((pow(v[j].x, 2) - pow(v[k].x, 2) + pow(v[j].y, 2) - pow(v[k].y, 2)) * (v[i].y - v[j].y)
                         - (pow(v[j].x, 2) - pow(v[i].x, 2) + pow(v[j].y, 2) - pow(v[i].y, 2)) * (v[k].y - v[j].y))
                         / ((v[i].x - v[j].x) * (v[k].y - v[j].y) * 2 - (v[k].x - v[j].x) * (v[i].y - v[j].y) * 2);
                cen.y = ((pow(v[j].y, 2) - pow(v[k].y, 2) + pow(v[j].x, 2) - pow(v[k].x, 2)) * (v[i].x - v[j].x)
                         - (pow(v[j].y, 2) - pow(v[i].y, 2) + pow(v[j].x, 2) - pow(v[i].x, 2)) * (v[k].x - v[j].x))
                         / ((v[i].y - v[j].y) * (v[k].x - v[j].x) * 2 - (v[k].y - v[j].y) * (v[i].x - v[j].x) * 2);
                r = dis(cen, v[i]);
            }
        }
    }

    if(abs(cen.x) < eps) cen.x = 0;
    if(abs(cen.y) < eps) cen.y = 0;

    return {r, cen};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cout << fixed;
    cout.precision(3);

    int N; cin >> N;

    vector<p> v(N);
    for(int i = 0; i < N; i++) cin >> v[i].x >> v[i].y;

    pair<double, p> circle = SmallestEnclosingCircle(v);
    cout << circle.second.x << " " << circle.second.y << "\n";
    cout << circle.first << "\n";

    return 0;
}
