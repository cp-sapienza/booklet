int bin_expo(int base, int exp, int mod) {
	int res = 1;
	for (; exp > 0; exp >>= 1) {
		if (exp & 1) res = (1LL * res * base) % mod;
		base = (1LL * base * base) % mod;
	}
	return res;
}
