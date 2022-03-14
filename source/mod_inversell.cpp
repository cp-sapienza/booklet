ll mod_inverse(ll x, ll mod) {
	return bin_expoll(x, mod - 2, mod);
}
