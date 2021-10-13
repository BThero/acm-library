#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

using namespace std;

typedef long long ll;

void fwht(ll a[], int n) {
	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) {
			for (int j = i; j < i + k; j++) {
				ll x = a[j], y = a[j + k];
				a[j] = x + y;
				a[j + k] = x - y;
			}
		}
	}
}

void fwht(vector<ll> a) {
	fwht(&a[0], sz(a));
}

int main() {
	return 0;
}

