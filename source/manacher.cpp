array<vector<int>,2> manacher(const string& s) {
	int n = s.size();
	array<vector<int>,2> p = {vector<int>(n), vector<int>(n)};
	for(int k = 0; k < 2; k++)
	for(int i = 0, l = 0, r = -1; i < n; i++) {
		if(i+k <= r) p[k][i] = min(p[k][l+r-i-k], r - i);
		int a = i-p[k][i]-1+k, b = i+p[k][i]+1;
		// if(!k && !p[k][i]) handle_pal(i,i);
		while(a >= 0 && b < n && s[a] == s[b]) {
			// handle_pal(a,b);
			p[k][i]++, a--, b++;
		}
		if(b-1 > r) l = a+1, r = b-1;
	}
	return p;
}