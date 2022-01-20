typedef array<ll, 4> matrix_t;

void fwht(ll a[], int n, array<ll, 4> M) {
    assert(n > 0 && (n & (n - 1)) == 0); 

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = i; j < i + k; j++) {
                ll x = a[j], y = a[j + k];
                a[j] = x * M[0] + y * M[2];
                a[j + k] = x * M[1] + y * M[3];
            }
        }
    }
}

vector<ll> conv_binary(vector<ll> a, vector<ll> b, int op) {
    static matrix_t direct[] = {
        {1, 1, 1, -1}, // xor
        {0, 1, 1, 1}, // and 
        {1, 1, 1, 0} // or
    };
    
    static matrix_t inverse[] = {
        {1, 1, 1, -1}, // xor inv
        {-1, 1, 1, 0}, // and inv
        {1, -1, 1, 0} // or inv
    };
    
    int n = 1;

    while (n < max(sz(a), sz(b))) {
        n *= 2;
    }

    a.resize(n);
    b.resize(n);
    fwht(a.data(), n, direct[op]);
    fwht(b.data(), n, direct[op]);

    for (int i = 0; i < n; i++) {
        a[i] *= b[i];
    }

    fwht(a.data(), n, inverse[op]);
    
    if (op == 0) { // only for xor
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
    
    return a;
}
