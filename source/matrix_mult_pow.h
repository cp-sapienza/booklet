#pragma once
#include "common.h"

using Matrix = vector<vector<ll>>;

Matrix mat_mul(const Matrix& a, const Matrix& b, ll mod) {
	assert(a[0].size() == b.size());

	Matrix res(a.size(), vector<ll>(b[0].size(), 0));
	for(int i = 0; i < ssize(res); i++)
		for(int j = 0; j < ssize(res[0]); j++)
			for(int k = 0; k < ssize(res[0]); k++)
				res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % mod;
	return res;
}

vector<ll> mat_mul(const Matrix& a, const vector<ll>& b, ll mod) {
	assert(a[0].size() == b.size());

	vector<ll> res(a.size(), 0);
	for(int i = 0; i < ssize(a); i++)
		for(int j = 0; j < ssize(a[0]); j++)
			res[i] = (res[i] + a[i][j] * b[j]) % mod;
	return res;
}

Matrix mat_pow(const Matrix& b, ll e, ll mod) {
	assert(b[0].size() == b.size());

	Matrix p(b), res(b.size(), vector<ll>(b.size(), 0));
	for(int i = 0; i < ssize(b); i++) res[i][i] = 1;
	for(; e; e /= 2) {
		if(e & 1) res = mat_mul(res, p, mod);
		p = mat_mul(p, p, mod);
	}
	return res;
}
