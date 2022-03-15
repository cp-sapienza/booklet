struct Fenwick2D {
	vector<vector<int>> ft;
	Fenwick2D(int n, int m) {
		ft.assign(n+1, vector<int>(m+1, 0));
	}
	void update(int x, int y, int v) {
		for(++x; x < ssize(ft); x += x&-x)
			for(int j = y+1; j < ssize(ft[0]); j += j&-j)
				ft[x][j] += v;
	}
	int query(int x, int y) {
		int res = 0;
		for(++x; x > 0; x -= x&-x)
			for(int j = y+1; j > 0; j -= j&-j)
				res += ft[x][j];
		return res;
	}
	int query(int x1, int y1, int x2, int y2) {
		return query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) + query(x1-1, y1-1);
	}
};