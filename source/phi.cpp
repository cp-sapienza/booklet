int phi(int n) {
	int res = n;
	for(int p = 2; p*p <= n; p++) {
		if(n % p == 0) {
			while(n % p == 0) n /= p;
			res -= res / p;
		}
	}
	if(n > 1) res -= res / n;
	return res;
}

vi phi_up_to_n(int n) {
	vi phi(n+1);
	for(int i = 0; i <= n; i++) phi[i] = i;
	for(int i = 2; i <= n; i++) if(phi[i] == i)
		for(int j = i; j <= n; j += i)
			phi[j] -= phi[j] / i;
	return phi;
}