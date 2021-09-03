typedef complex<double> C;

void fft(vector<C> &a) {
	int n = sz(a), m = n / 2;
	vector<int> rev(n, 0);

	for (int i = 0; i < n; i++) {
		rev[i] = i & 1 ? (rev[i - 1] | m) : (rev[i / 2] / 2);
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	}

	vector<C> root(n);

	for (int i = n - 1; i; i--) {
		if (i >= m) {
			double alph = 2.0 * M_PI * (i ^ m) / n;
			root[i] = C(cos(alph), sin(alph));
		}
		else {
			root[i] = root[2 * i];
		}
	}

	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) { 
			for (int j = 0; j < k; j++) {
				C z = root[j + k] * a[i + j + k];
				a[i + j + k] = a[i + j] - z;
				a[i + j] += z;
			}
		}
	}
}

vector<ll> conv(const vector<ll> &a, const vector<ll> &b) {
	if (a.empty() || b.empty()) {
		return {};
	}

	vector<ll> res(sz(a) + sz(b) - 1, 0);
	int L = 32 - __builtin_clz(sz(res)), n = (1 << L);
	vector<C> in(n), out(n);

	for (int i = 0; i < n; i++) {
		if (i < sz(a)) in[i].real(a[i]);
		if (i < sz(b)) in[i].imag(b[i]);
	}
	
	fft(in);
	
	for (C &x : in) {
		x *= x;
	}
    
	for (int i = 0; i < n; i++) {
		out[i] = in[-i & (n - 1)] - conj(in[i]);
	}

	fft(out);

	for (int i = 0; i < sz(res); i++) {
		res[i] = llround(out[i].imag() / (4 * n));
	}

	return res;
}
