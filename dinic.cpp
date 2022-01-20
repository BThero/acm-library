template <class C> struct edge {
    int from, to;
    C f, c;

    edge(int u, int v, C c) : from(u), to(v), f(0), c(c) {}
};

template <class C> struct dinic {
    vector<int> d, ptr, q;
    vector<vector<int>> g;
    vector<edge<C>> e;
    int n, S, T;

    dinic() : n(0), S(-1), T(-1) {}
    dinic(int _n) : n(_n), g(_n), d(_n), ptr(_n), q(_n) {}

    void add_edge(int u, int v, C c) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);

        g[u].pb(sz(e));
        e.pb(edge(u, v, c));
        g[v].pb(sz(e));
        e.pb(edge(v, u, 0));
    }

    void set(int _S, int _T) {
        S = _S;
        T = _T;
        assert(0 <= S && S < n);
        assert(0 <= T && T < n);
    }

    bool bfs(int st, int en) {
        assert(0 <= st && st < n);
        assert(0 <= en && en < n);

        fill(all(d), -1);
        int l = 0, r = 0;
        q[r++] = st;
        d[st] = 0;
        
        while (l < r) {
            int v = q[l++];

            for (int id : g[v]) {
                int to = e[id].to;
                
                if (e[id].f != e[id].c && d[to] == -1) {
                    d[to] = d[v] + 1;
                    q[r++] = to;
                }
            }
        }
        
        return d[en] != -1;
    }

    C dfs(int v, C flow) {
        if (v == T || flow == 0) {
            return flow;
        }

        for (; ptr[v] < sz(g[v]); ptr[v]++) {
            int id = g[v][ptr[v]];
            int to = e[id].to;

            if (d[to] != d[v] + 1) {
                continue;
            }

            C pushed = dfs(to, min(flow, e[id].c - e[id].f));

            if (pushed > 0) {
                e[id].f += pushed;
                e[id ^ 1].f -= pushed;
                return pushed;
            }
        }

        return 0;
    }

    C flow(C lim = numeric_limits<C>::max()) {
        assert(0 <= S && S < n);
        assert(0 <= T && T < n);

        C res = 0;

        while (bfs(S, T)) {
            fill(all(ptr), 0);

            while (C pushed = dfs(S, lim)) {
                res += pushed;
                lim -= pushed;
            }
        }

        return res;
    }
};
