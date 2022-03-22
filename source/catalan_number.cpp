int catalan_number(int n, int mod) {
	assert(factorial.size() > 2 * n);
	return return (((factorial[2 * n] * inv_factorial[n + 1]) % mod) * inv_factorial[n]) % mod;
}
