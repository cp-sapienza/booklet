struct Fenwick2D {
	vector<vector<ll>> ft;
	Fenwick2D(int n, int m) {
		ft.assign(n+1, vector<ll>(m+1, 0));
	}
	void update(int x, int y, ll v) {
		for(++x; x < ssize(ft); x += x&-x)
			for(int j = y+1; j < ssize(ft[0]); j += j&-j)
				ft[x][j] += v;
	}
	ll query(int x, int y) {
		ll res = 0;
		for(++x; x > 0; x -= x&-x)
			for(int j = y+1; j > 0; j -= j&-j)
				res += ft[x][j];
		return res;
	}
	ll query(int x1, int y1, int x2, int y2) {
		return query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) + query(x1-1, y1-1);
	}
};