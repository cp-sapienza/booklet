int catalan_number(int n, int mod) {
	assert(factorial.size() > 2 * n);
	return (((fact[2 * n] * invfact[n + 1]) % mod) * invfact[n]) % mod;
}
