#include <bits/stdc++.h>

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pb push_back

using namespace std;

typedef long long ll;
const int N = 1e5+5;
struct fast_kuhn {
	int for_left[N], for_right[N]; // пара в парасочетании для каждой доли

	int used_kuhn[N], timer;
	vector < int > g[N];
	
	void add_edge(int x, int y) { //добавляет ребро с левой доли на правую
		g[x].pb(y);
	}

	bool dfs (int v) {
		if(used_kuhn[v] == timer) return false;
		used_kuhn[v] = timer;
		
		for (int to : g[v]) {
			if(for_right[to] == -1 || dfs(for_right[to])) {
				for_right[to] = v;
				for_left[v] = to;
				return true;
			}
		}
		
		return false;
	}

	vector < pair<int,int> > matching(vector < int > nodes) {
		random_shuffle(all(nodes));
		memset(for_right, -1, sizeof for_right);
		memset(for_left, -1, sizeof for_left);
		
		
		for (int v : nodes) {
			random_shuffle(all(g[v]));
			for (int to : g[v])
				if(for_right[to] == -1) {
					for_right[to] = v;
					for_left[v] = to;
					break;
				}
		}
		//жадное инициализацию + рандомизация порядка вершин и ребер
		
		for (int run = 1; run; ) {
			run = 0;
			++timer;
			for (int v : nodes) {
				if(for_left[v] == -1 && dfs(v))
					run = 1;
			}
		}
		
		vector <pair<int,int>> res;
		for (int v : nodes)
			res.pb({v, for_left[v]}); //v, -1 нет пары
		return res;
	}
};

