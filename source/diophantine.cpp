bool diophantine(ll a, ll b, ll c, ll& x0, ll& y0, ll& g) {
	auto e = egcd(abs(a), abs(b));
	g = e[2];
	if (c % g) return false;
	x0 = e[0] * (c / g), y0 = e[1] * (c / g);
	if (a < 0) x0 = -x0;
	if (b < 0) y0 = -y0;
	return true;
}
