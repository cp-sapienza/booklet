using ld = long double;
using C = complex<ld>;

void fft(vector<C>& a) {
	int n = ssize(a), L = 31 - __builtin_clz(n);
	static vector<C> R(2, 1);
	static vector<C> rt(2, 1);
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for (int i = k; i < 2 * k; ++i)
			rt[i] = R[i] = (i & 1) ? R[i / 2] * x : R[i / 2];
	}
	vi rev(n);
	for (int i = 0; i < n; ++i)
		rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for (int i = 0; i < n; ++i)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
			for (int j = 0; j < k; ++j) {
				auto x = (ld *) &rt[j + k], y = (ld *) &a[i + j + k];
				C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
				a[i + j + k] = a[i + j] - z;
				a[i + j] += z;
		}
}

vector<ld> conv(const vector<ld>& a, const vector<ld>& b) {
	if (a.empty() || b.empty()) return {};
	vector<ld> res(a.size() + b.size() - 1);
	int L = 32 - __builtin_clz(ssize(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	for (int i = 0; i < ssize(b); ++i) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	for (int i = 0; i < n; ++i) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	for (int i = 0; i < ssize(res); ++i) res[i] = imag(out[i]) / (4 * n);
	return res;
}

vector<ll> mod_conv(const vector<ll>& a, const vector<ll>& b, int mod) {
	if (a.empty() || b.empty()) return {};
	vector<ll> res(a.size() + b.size() - 1);
	int B = 32-__builtin_clz(ssize(res)), n = 1 << B, cut = int(sqrt(mod));
	vector<C> L(n), R(n), outs(n), outl(n);
	for (int i = 0; i < ssize(a); ++i) L[i] = C((int) a[i] / cut, (int) a[i] % cut);
	for (int i = 0; i < ssize(b); ++i) R[i] = C((int) b[i] / cut, (int) b[i] % cut);
	fft(L), fft(R);
	for (int i = 0; i < n; ++i) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0L * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0L * n) / C(.0L, 1.0L);
	}
	fft(outl), fft(outs);
	for (int i = 0; i < ssize(res); ++i) {
		ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
		ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
		res[i] = ((av % mod * cut + bv) % mod * cut + cv) % mod;
	}
	return res;
}