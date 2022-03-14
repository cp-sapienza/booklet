ll crt(const vector<ll>& a, const vector<ll>& n) {
	ll res = a[0], l = n[0];
	for (int i = 1; i < ssize(a); ++i) {
		auto [x, _, g] = egcd(l, n[i]);
		if ((a[i] - res) % g != 0) return -1;
		res += x * (a[i] - res) / g % (n[i] / g) * l;
		res = (res + l * n[i] / g) % (l * n[i] / g);
		l = lcm(l, n[i]);
	}
	return res;
}
