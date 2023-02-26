#pragma once
#include "common.h"
#include "factorial.h"

int n_choose_k(int n, int k, int mod) {
	assert(n >= k);
	assert(ssize(factorial) > n);
	return (((factorial[n] * inv_factorial[k]) % mod) * inv_factorial[n - k]) % mod;
}
