ll mod_mul(ll a, ll b, ll mod) {
	ll res = 0;
	for (a %= mod, b %= mod; b != 0; b >>= 1, a = (a << 1) % mod)
		if (b & 1) res = (res + a) % mod;
	return res;
}