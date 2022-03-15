vector<pair<int,int>> lyndon(const string& s) {
	int n = s.size(), j, k;
	vector<pair<int,int>> fact;
	for(int i = 0; i < n; ) {
		for(j = i+1, k = i; j < n && s[k] <= s[j]; j++)
			if(s[k] < s[j]) k = i;
			else k++;
		while(i <= k) fact.push_back({i,j-k}), i += j-k;
	}
	return fact;
}