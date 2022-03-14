int mod_inverse(int x, int mod) {
	return bin_expo(x, mod - 2, mod);
}
