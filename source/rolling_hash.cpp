vector<pair<ll,int>> substring_hashes(const string& s, int len) {
	const ll b = 26, mx = 1000000007, my = 1000000009;

	if(s.size() < len) return {};
	ll x = 0, y = 0, px = 1, py = 1;
	for(int i = 0; i < len; i++) {
		x = (x * b + s[i]) % mx;
		y = (y * b + s[i]) % my;
		px = (px * b) % mx;
		py = (py * b) % my;
	}
	vector<pair<ll,int>> res = {{(x<<32)+y, 0}};
	for(int i = len; i < s.size(); i++) {
		x = (x * b + s[i]) % mx;
		y = (y * b + s[i]) % my;
		x = ((x - s[i-len] * px) % mx + mx) % mx;
		y = ((y - s[i-len] * py) % my + my) % my;
		res.push_back({(x<<32)+y, i-len+1});
	}
	return res;
}
ll string_hash(const string& s) { return substring_hashes(s, s.size())[0].first; }
