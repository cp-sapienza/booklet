vector<ll> factorial;
vector<ll> inv_factorial;

void init_factorials(int n, int mod) { // [0, n]
	factorial.resize(n);
	inv_factorial.resize(n);
	factorial[0] = 1;
	for (int i = 1; i <= n; ++i)
		factorial[i] = (i * factorial[i - 1]) % mod;
	inv_factorial[n] = mod_inverse(factorial[n], mod);
	for (int i = n - 1; i >= 0; --i)
		inv_factorial[i] = ((i + 1) * inv_factorial[i + 1]) % mod;
}
