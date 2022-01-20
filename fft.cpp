typedef complex<double> cd;

void fft(vector<cd> &a) {
    int n = sz(a), m = n / 2;
    vector<int> rev(n, 0);

    for (int i = 0; i < n; i++) {
        rev[i] = i & 1 ? (rev[i - 1] | m) : (rev[i / 2] / 2);
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    vector<cd> root(n);
    vector<complex<long double>> croot(n);
    root[1] = croot[1] = 1.0;

    for (int k = 2; k < n; k *= 2) {
        complex<long double> x = polar(1.0L, acosl(-1.0L) / k);

        for (int i = k; i < 2 * k; i++) {
            root[i] = croot[i] = i & 1 ? croot[i / 2] * x : croot[i / 2];
        }
    }

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) { 
            for (int j = 0; j < k; j++) {
                cd z = root[j + k] * a[i + j + k];
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
    int n = 1;

    while (n < sz(res)) {
        n *= 2;
    }

    vector<cd> in(n), out(n);

    for (int i = 0; i < n; i++) {
        if (i < sz(a)) in[i].real(a[i]);
        if (i < sz(b)) in[i].imag(b[i]);
    }

    fft(in);

    for (cd &x : in) {
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

vector<ll> convMod(const vector<ll> &a, const vector<ll> &b, int M) {
    if (a.empty() || b.empty()) {
        return {};
    }

    vector<ll> res(sz(a) + sz(b) - 1, 0);
    int L = 32 - __builtin_clz(sz(res)), n = (1 << L), cut = (int)sqrt(M);
    vector<cd> inA(n), inB(n), outA(n), outB(n);

    for (int i = 0; i < n; i++) {
        if (i < sz(a)) inA[i] = cd(a[i] / cut, a[i] % cut);
        if (i < sz(b)) inB[i] = cd(b[i] / cut, b[i] % cut);
    }

    fft(inA);
    fft(inB);

    for (int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        cd ax = inA[i] + conj(inA[j]);
        cd ay = inA[i] - conj(inA[j]);
        cd bx = inB[i] + conj(inB[j]);
        cd by = inB[i] - conj(inB[j]);
        outA[j] = (ax * bx + ax * by) / (4.0 * n);
        outB[j] = (ay * by * -1.0 + ay * bx) / (4.0 * n);
    }

    fft(outA);
    fft(outB);

    for (int i = 0; i < sz(res); i++) {
        ll p = llround(outB[i].real()) % M;
        ll q = (llround(outA[i].imag()) + llround(outB[i].imag())) % M;
        ll r = llround(outA[i].real()) % M;
        res[i] = ((r * cut % M + q) * cut % M + p) % M;
    }

    return res;
}
