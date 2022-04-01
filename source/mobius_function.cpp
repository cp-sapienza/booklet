vi mu_up_to_n(int n) {
	vi mu(n + 1), lpf(n + 1);
	for (ll p = 2; p <= n; ++p)
		if (!lpf[p]) {
			lpf[p] = p;
			for (ll k = p * p; k <= n; k += p)
				if (!lpf[k])
					lpf[k] = p;
		}
	mu[1] = 1;
	for (int i = 2; i <= n; ++i)
		if (lpf[i / lpf[i]] == lpf[i]) mu[i] = 0;
		else mu[i] = -1 * mu[i / lpf[i]];
	return mu;
}
