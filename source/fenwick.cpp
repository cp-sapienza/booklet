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
};