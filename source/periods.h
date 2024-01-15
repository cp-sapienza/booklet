#pragma once
#include "common.h"
#include "z_func.h"

vi periods(string s) {
	vi z = z_function(s), p;
	int n = ssize(z);
	for(int i = 1; i < n; i++) {
		// if(n%i == 0) // uncomment for no trailing subperiods
		if(z[i]+i == n)
			p.push_back(i);
	}
	p.push_back(n);
	return p;
}