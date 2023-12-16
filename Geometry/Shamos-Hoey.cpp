// Shamos-hoey 알고리즘
// main함수 사용 예시는 boj 20150
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

struct Point {
    ll x, y;

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator>(const Point& other) const {
        return other < *this;
    }

    bool operator<=(const Point& other) const {
        return !(other < *this);
    }
};



ll x_cur, k = 1e9 + 7, t;
struct Line {
	Point a, b; int idx; // a <= b
	ld Eval() const { return 1.l * (b.y - a.y) / (b.x - a.x) * (x_cur - a.x) + a.y; }
	bool operator< (const Line& i) const {
		if (ld t = Eval() - i.Eval(); abs(t) > 1e-6) return t < 0;
		return idx < i.idx;
	}
	friend istream& operator>> (istream& in, Line& L) {
		in >> L.a.x >> L.a.y >> L.b.x >> L.b.y;
		t = L.a.x + k * L.a.y; L.a.y -= k * L.a.x; L.a.x = t;
		t = L.b.x + k * L.b.y; L.b.y -= k * L.b.x; L.b.x = t;
		if (L.a > L.b) swap(L.a, L.b);
		return in;
	}
};

struct Event {
    ll x, y; int t, idx;
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        if (t != other.t) return t < other.t;
        return y < other.y;
    }
};


int CCW(const Point& a, const Point& b, const Point& c) {
	ld ret = 1.l * (b.x - a.x) * (c.y - b.y) - 1.l * (c.x - b.x) * (b.y - a.y);
	return abs(ret) > 1e-6 ? ret > 0 ? 1 : -1 : 0;
}

bool IsCross(const Line& a, const Line& b) {
	int t1 = CCW(a.a, a.b, b.a) * CCW(a.a, a.b, b.b);
	int t2 = CCW(b.a, b.b, a.a) * CCW(b.a, b.b, a.b);
	if (t1 < 0 && t2 < 0) return 1;
	if (t1 == 0 && t2 == 0) return b.a <= a.b && a.a <= b.b;
	return t1 <= 0 && t2 <= 0;
}

bool shamosHoey(const vector<Line>& v) {
	const int n = v.size();
	vector<Event> E; multiset<Line> S;
	for (int i = 0; i < n; i++) {
		E.push_back({ v[i].a.x, v[i].a.y, 0, i });
		E.push_back({ v[i].b.x, v[i].b.y, 1, i });
	}
	sort(E.begin(), E.end());
	for (const auto& [x, y, t, idx] : E) {
		x_cur = x;
		if (t == 0) {
			auto it = S.insert(v[idx]);
			if (next(it) != S.end() && IsCross(v[idx], *next(it))) return 1;
			if (it != S.begin() && IsCross(v[idx], *prev(it))) return 1;
		}
		else {
			auto it = S.lower_bound(v[idx]);
			if (it != S.begin() && next(it) != S.end() && IsCross(*prev(it), *next(it))) return 1;
			S.erase(it);
		}
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int n; cin >> n;
	vector<Line> v(n);
	for (int i = 0; i < n; i++) cin >> v[i], v[i].idx = i;
	cout << shamosHoey(v);
    return 0;
}
