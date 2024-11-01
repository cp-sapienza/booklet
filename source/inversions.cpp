#pragma once
#include "common.h"
#include "fenwick.h"

ll inversions(vi p)
{
	int n = ssize(p);
	Fenwick ft(n);
	vi pos(n);
	for(int i=0; i < n; i++)
		pos[p[i]] = i;
	ll res = 0;
	for(int i = 0; i < n; i++) {
		res += ft.sum(0, pos[i]);
		ft.add(pos[i], -1);
	}
	return res;
}
