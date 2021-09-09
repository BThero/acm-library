#include <bits/stdc++.h>

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pb push_back

using namespace std;

typedef long long ll;
typedef long double ld;

struct Line {
	ld m, b;
	ld operator() (ld x) { return m * x + b; }
};

const int N = 5e6 + 5;
//для максимума реализация
struct liChaoTree {
	Line t[N];
	int l_son[N], r_son[N], Sz, root;
	
	void add_line(int &v, int l, int r, Line x) {
		if(!v) {
			v = ++Sz;
			t[v] = x;
			return;
		}
		if (l == r) {
			if(x(l) > t[v](l)) t[v] = x;
			return;
		}
		
		int md = (l+r) >> 1;
		if (t[v].m > x.m) swap(t[v], x);
		
		if (t[v](md) < x(md)) {
			swap(x, t[v]);
			add_line(l_son[v], l, md, x);
		} else {
			add_line(r_son[v], md + 1, r, x);
		}
	}
	
	ld query(int v, int l, int r, int x) {
		if(!v) return -8e18;
		if (l == r) return t[v](x);
		
		int md = (l+r) >> 1;
		ld res = t[v](x);
		if (x <= md) res = max(res, query(l_son[v], l, md, x));
		else res = max(res, query(r_son[v], md + 1, r, x));
		
		return res;
	}
	
	void add(ld m, ld b) {
		Line x;
		x.m = m, x.b = b;
		//меняем границы l и r смотря на границы запроса x
		add_line(root, -1e9, 1e9, x);
	}
	
	ld get(int x) {
		
		//меняем границы l и r смотря на границы запроса x
		return query(root, -1e9, 1e9, x);
	}
};
