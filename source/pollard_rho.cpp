ll pollard_rho(ll n) {
	if (n < 2) return n;
	if (n % 2 == 0) return 2;
	if (miller_rabin(n)) return n;
	srand(time(NULL));
	ll x = (rand() % (n - 2)) + 2;
	ll c = (rand() % (n - 1)) + 1;
	ll y = x, g = 1;
	auto f = [&](ll a, ll b) { return (mod_mul(a, a, n) + b) % n; };
	while (g == 1 || g == n) {
		x = f(x, c), y = f(f(y, c), c);
		g = gcd(abs(x - y), n);
		if (g == n) {
			x = (rand() % (n - 2)) + 2;
			c = (rand() % (n - 1)) + 1;
		}
	}
	return pollard_rho(g);
}
