ll mod_inverse(ll n, ll mod) {
	auto [x,y,g] = egcd(n, mod);
	if(g != 1) return -1;
	return (x % mod + mod) % mod;
}