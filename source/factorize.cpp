vector<pair<ll, int>> factorize(ll n) {
	vector<pair<ll, int>> factors;
	while (n > 1) {
		pair<ll, int> f = {pollard_rho(n), 0};
		while (n % f.first == 0)
			n /= f.first, ++f.second;
		factors.push_back(f);
	}
	sort(all(factors));
	return factors;
}
