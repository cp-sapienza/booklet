ll linear_recurrence(const vector<ll>& a, const vector<ll>& b, const vector<ll>& x, ll n, ll mod) {
	int k = a.size(), h = b.size();
	Matrix m(k+h, vector<ll>(k+h, 0));

	for(int i = 0; i < k-1; i++) m[i][i+1] = 1;
	for(int i = 0; i < k; i++) m[k-1][i] = a[k-i-1];
	for(int i = 0; i < h; i++) m[k-1][k+i] = b[i];
	for(int i = 0; i < h; i++) {
		m[k+i][k] = 1;
		for(int j = 1; j <= i; j++)
			m[k+i][k+j] = (m[k+i-1][k+j-1] + m[k+i-1][k+j]) % mod;
	}

	vector<ll> xx(k+h, 1);
	for(int i = 0; i < k; i++) xx[i] = x[i];

	auto res = mat_mul(mat_pow(m, n, mod), xx, mod);
	return (res[0] % mod + mod) % mod;
}