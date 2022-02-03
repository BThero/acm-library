int det_mod(vector<vector<int>> a, int M) {
    assert(!a.empty());
    assert(sz(a) == sz(a[0]));

	int n = sz(a);
	int res = 1;

	for (int i = 0; i < n; ++i) {
	    int k = i;

	    for (int j = i + 1; j < n; ++j) {
	        if (a[j][i] > 0) {
	            k = j;
                break;
	        }
	    }

	    if (a[k][i] == 0) {
	        return 0;
	    }

        swap(a[i], a[k]);

	    if (i != k) {
	        res = (M - res) % M;
	    }

	    res = (res * 1ll * a[i][i]) % M;
	    int inv = bpow(a[i][i], M - 2, M);

	    for (int j = i + 1; j < n; ++j) {
	    	a[i][j] = (a[i][j] * 1ll * inv) % M;
	    }

	    for (int j = 0; j < n; ++j) {
	        if (j != i && a[j][i] != 0) {
	            for (int k = i + 1; k < n; ++k) {
	            	a[j][k] = ((a[j][k] - a[i][k] * 1ll * a[j][i]) % M + M) % M;
	            }
	        }
	    }
	}

	return res;
}

