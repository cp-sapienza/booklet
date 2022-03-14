bool miller_rabin(ll n) {
	if (n < 2) return false;
	int r = 0;
	ll d = n - 1;
	while ((d & 1) == 0) d >>= 1, ++r;
	for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
		if (n == a) return true;
		ll x = bin_expoll(a, d, n);
		bool composite = true;
		if (x == 1 || x == n - 1)
			composite = false;
		for (int _ = 0; _ < r - 1 && composite; ++_) {
			x = mod_mul(x, x, n);
			if (x == n - 1) composite = false;
		}
		if (composite) return false;
	}
	return true;
}
