#include "common.h"
#include "factorial.cpp"

int n_choose_k(int n, int k, int mod) {
	assert(n >= k);
	assert(factorial.size() > n);
	return (((factorial[n] * inv_factorial[k]) % mod) * inv_factorial[n - k]) % mod;
}
