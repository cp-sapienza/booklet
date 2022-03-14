int n_choose_k(int n, int k, int mod) {
	assert(n >= k);
	assert(factorial.size() >= n);
	int x = (factorial[n] * inv_factorial[k]) % mod;
	int y = (x * inv_factorial[n - k]) % mod;
	return y;
}
