#pragma once
#include "common.h"
#include "factorial.h"

int catalan_number(int n, int mod) {
	assert(ssize(factorial) > 2 * n);
	return (((factorial[2 * n] * inv_factorial[n + 1]) % mod) * inv_factorial[n]) % mod;
}
