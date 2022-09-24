#pragma once
#include "common.h"

struct Fenwick {
	using Value = ll;

	vector<Value> ft;
	Fenwick(int N) { ft.assign(N+1, 0); }
	template<typename T> Fenwick(const vector<T>& data) {
		ft.push_back(0);
		ft.insert(ft.end(), data.begin(), data.end());
		for(int i = 1, j = 2; i < ssize(ft); ++i, j = i+(i&-i))
			if(j < ssize(ft))
				ft[j] += ft[i];
	}
	void add(int p, Value v) {
		for(++p; p < ssize(ft); p += p&-p) ft[p] += v;
	}
	Value sum(int b) {
		Value res = 0;
		for(++b; b > 0; b -= b&-b) res += ft[b];
		return res;
	}
	// [a, b]
	Value sum(int a, int b) { return sum(b) - (a?sum(a-1):0); }
	Value get(int p) { return sum(p, p); }
	void set(int p, Value v) { add(p, v - get(p)); }

	/* Optional. If the fenwick has no negative values returns the smallest i
		for which sum(0, i) >= k in O(log N) (or -1 if such i does not exist)
	*/
	int lower_bound(Value k) {
	int t, res = 0;
	t = 1 << (__builtin_clz(1)-__builtin_clz(ssize(ft)));
	while(t) {
		if(t+res < ssize(ft)-1 && ft[t+res] < k) {
		//                                  ^<= for upper_bound
			res += t;
			k -= ft[res];
		}
		t /= 2;
	}
	return ft[res+1] < k? -1 : res;
}

};