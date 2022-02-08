// bpow required!

const int MOD = (119 << 23) + 1, root = 62; // = 998244353

// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.

void ntt(vector<ll> &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<ll> rt(2, 1);

	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, bpow(root, MOD >> s)};

        for (int i = k; i < 2 * k; i++) {
            rt[i] = rt[i / 2] * z[i & 1] % MOD;
        }
	}

	vector<int> rev(n);

	for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    }

	for (int i = 0; i < n; i++) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }

	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                ll z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
                a[i + j + k] = ai - z + (z > ai ? MOD : 0);
                ai += (ai + z >= MOD ? z - MOD : z);
            }
        }
    }
}

vector<ll> conv(const vector<ll> &a, const vector<ll> &b) {
	if (a.empty() || b.empty()) return {};

	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	int inv = bpow(n, MOD - 2);

	vector<ll> L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);

    for (int i = 0; i < n; i++) {
	    out[-i & (n - 1)] = (ll)L[i] * R[i] % MOD * inv % MOD;
    }

	ntt(out);
	return {out.begin(), out.begin() + s};
}

