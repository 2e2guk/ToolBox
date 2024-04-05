// Persistant Segment Tree
// query는 구간 합 쿼리
// main함수 예시는 boj 11012 Egg
#include<bits/stdc++.h>
using namespace std;

#define mp(a, b) make_pair((a),(b)) 
#define lbi(X, n) int(lower_bound(X.begin(), X.end(), n) - begin(X))  
#define ubi(X, n) int(upper_bound(X.begin(), X.end(), n) - begin(X))

const int YMAX = 1e5 + 5, inf = 1e9; 
typedef long long ll;

// l = 왼쪽 자식, r = 오른쪽 자식, v = 현재 노드
struct Node { int l = -1, r = -1, v = 0; };  

template<typename IndexType, typename ValueType>
struct PST {  
    // version 관리를 위한, vector<int>
    vector<ValueType> version;  
    IndexType N;  
    vector<Node> tree;  
    
    PST(IndexType n) : N(n) {  
        tree.push_back({});  
        version.push_back(0);  
    }  
    IndexType update(IndexType i, ValueType v) {  
        IndexType prev_root = version.back();  
        // 업데이트 과정에서의 root은, 기존의 PST의 마지막 index의 다음 값을 가지게 되므로, tree.size() 를 할당하면 된다. 
        IndexType root = tree.size(); 
        tree.push_back({});
        // version 벡터에, 현재 PST의 root를 저장한다. 
        version.push_back(root);  
        update(prev_root, root, 0, N - 1, i, v);  
        // 업데이트가 끝난 후, 새로운 버전의 index를 반환한다. version.size()-1을 반환하는 이유는, 0-based index이기 때문이다. 
        return version.size() - 1;  
    }  
    ValueType query(IndexType version_idx, IndexType l, IndexType r) {  
        // version[version_idx]에는, version_idx에 해당하는 버전의 루트 노드의 번호가 저장된다. 
        return query(version[version_idx], 0, N - 1, l, r);  
    }  
private:  
    void update(IndexType prev, IndexType cur, IndexType nl, IndexType nr, IndexType i, IndexType v) {  
        // 현재 노드가 없거나, 현재 노드가 표현하는 구간에, 업데이트하려는 인덱스가 포함되지 않는 경우, 아무 작업도 하지 않는다. 
        if (cur == -1 || nr < i || nl > i) return;  
        // leaf node인 경우.
        if (nl == nr) {  
            tree[cur].v += v;  
            return;  
        }  
        // For convenience, makes previous tree always has node in this place  
        if (tree[prev].l == -1) {  
            tree[prev].l = tree.size();  
            tree[prev].r = tree.size() + 1;  
            tree.push_back({}), tree.push_back({});  
        }  
    
        IndexType m = nl + (nr - nl) / 2;  
        // 왼쪽 자식 노드를 업데이트해야 하는 경우. 오른쪽 자식 노드는 그대로 사용한다. 
        if (i <= m) {  
            IndexType new_child = tree.size();  
            tree.push_back(tree[tree[prev].l]);  
            tree[cur].l = new_child;  
            tree[cur].r = tree[prev].r;  
            update(tree[prev].l, tree[cur].l, nl, m, i, v);  
        } 
        // 오른쪽 자식 노드를 업데이트해야 하는 경우. 왼쪽 자식 노드는 그대로 사용한다. 
        else {  
            IndexType new_child = tree.size();  
            tree.push_back(tree[tree[prev].r]);  
            tree[cur].l = tree[prev].l;  
            tree[cur].r = new_child;  
            update(tree[prev].r, tree[cur].r, m + 1, nr, i, v);  
        }  
    
        tree[cur].v = (~tree[cur].l ? tree[tree[cur].l].v : 0) + (~tree[cur].r ? tree[tree[cur].r].v : 0);  
    }  
    // n = 노드 번호, nl, nr = 노드가 관할하는 구간, l, r = 쿼리를 날리는 구간
    ValueType query(IndexType n, IndexType nl, IndexType nr, IndexType l, IndexType r) {  

        if (n == -1 || nr < l || nl > r) return 0;  
        if (nl >= l && nr <= r) return tree[n].v;  
        IndexType m = nl + (nr - nl) / 2;  
        return query(tree[n].l, nl, m, l, r) + query(tree[n].r, m + 1, nr, l, r);  
    }  
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
	PST<int, int> pst(YMAX);  
	int T; cin >> T;
	vector<int> res;
	while(T--) {
		int n, m; cin >> n >> m;  
		vector<pair<int, int>> query(n);  
		for (auto&[x, y]: query)cin >> x >> y;  
		sort(query.begin(), query.end());  
		
		vector<pair<int, int>> versions;  
		for (auto&[x, y]: query) {  
			int version_idx = pst.update(y, 1);  
			versions.push_back({x, version_idx});  
		}  
		int vidx = pst.update(YMAX - 1, 0);  
		versions.push_back({1e9, vidx});  
		
		ll ans = 0;  
		while (m--) {  
			int x1, x2, y1, y2; cin >> x1 >> x2 >> y1 >> y2;  
			if (x1 > x2) swap(x1, x2);  
			if (y1 > y2) swap(y1, y2);  
		
			// x2 보다 큰 버전들 중 가장 먼저 나오는 것의 바로 이전 버전  
			int version_right = versions[ubi(versions, mp(x2, inf))].second - 1;  
			int t = pst.query(version_right, y1, y2);  
		
			// x1 보다 같거나 큰 버전들 중 가장 먼저 나오는 것의 바로 이전 버전  
			int version_left = versions[lbi(versions, mp(x1, -inf))].second - 1;  
			t -= pst.query(version_left, y1, y2);  
			ans += t;  
		}  
		res.push_back(ans);
	}  
	for(const auto& ele : res) cout << ele << "\n";
	return 0; 
} 
