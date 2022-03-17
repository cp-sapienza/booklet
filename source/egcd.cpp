array<ll,3> egcd(ll a, ll b) {
	ll x = 1, y = 0;
	ll x1 = 0, y1 = 1, a1 = a, b1 = b;
	while(b1) {
		ll q = a1 / b1;
		tie(x, x1) = make_pair(x1, x - q * x1);
		tie(y, y1) = make_pair(y1, y - q * y1);
		tie(a1, b1) = make_pair(b1, a1 - q * b1);
	}
	return {x, y, a1};
}