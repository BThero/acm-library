#include <bits/stdc++.h>

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pb push_back

using namespace std;

typedef long long ll;
const int N = 1e5+5;
struct HopcroftKarp {
	int used[N], for_left[N], for_right[N], level[N], timer;
	vector < int > g[N]; //ребро исходят только с левой доли
	void init(int n) {
		for (int i = 1; i <= n; ++i)
			g[i].clear();
	}
	
	void add(int x, int y) {
		g[x].pb(y);
	}
	
	queue<int> Q;
	
	bool dfs (int v) {
		if(used[v] == timer) return false;
		used[v] = timer;
		
		for (int to : g[v]) {
			int u = for_right[to];
			if(u == -1 || (level[u] > level[v] && dfs(u))) {
				for_right[to] = v;
				for_left[v] = to;
				return true;
			}
		}
		
		return false;
	}
	
	vector < pair<int,int> > matching(vector <int> nodes) { //левая доля
		memset(for_left, -1, sizeof for_left);
		memset(for_right, -1, sizeof for_right);
		memset(used, 0, sizeof used);
		memset(level, 0, sizeof level);
		
		
		timer = 0;
		random_shuffle(all(nodes));
		
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
		
		for(int run = 1; run; ) {
			run = 0;
			for (int v : nodes) {
				if (for_left[v] == -1) {
					Q.push(v);
					level[v] = 0;
				} else {
					level[v] = -1;
				}
			}
			while(sz(Q)) {
				int v = Q.front(); Q.pop();
				for (int to : g[v]) {
					int u = for_right[to];
					if(u != -1 && level[u] < 0) {
						level[u] = level[v] + 1;
						Q.push(u);
					}
				}
			}
			
			timer++;
			for (int v : nodes) if (for_left[v] == -1 && dfs(v)) {
				run = 1;
			}
			if(!run) break;
		}
		
		vector <pair<int,int>> res;
		for (int v : nodes)
			res.pb({v, for_left[v]}); //v, -1 нет пары
		return res;
	}
};
