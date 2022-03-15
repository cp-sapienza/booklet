vector<bool> eratosthenes(int n) {
	vector<bool> prime(n+1, true);
	prime[0] = prime[1] = false;
	for(ll p = 2; p <= n; p++) if(prime[p]) {
		// primes.push_back(p);
		for(ll k = p*p; k <= n; k += p)
			prime[k] = false;
	}
	return prime;
}