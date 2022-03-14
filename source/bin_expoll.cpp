ll bin_expoll(ll base, ll exp, ll mod) {
	ll result = 1;
	for (; exp > 0; exp >>= 1) {
		if (exp & 1) result = mod_mul(result, base, mod);
		base = mod_mul(base, base, mod);
	}
	return result;
}
