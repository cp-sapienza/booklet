vi z_function(string s) {
	int n = s.size();
	vi z(n, 0);
	for(int i = 1, l = 0, r = 0; i < n; i++) {
		if(i <= r) z[i] = min(r-i+1, z[i-l]);
		while(i+z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
		if(i+z[i]-1 > r) l = i, r = i + z[i] - 1;
	}
	// z[0] = n; // Add this if you need z[0]=n instead of z[0]=0
	return z;
}

// Find occurrences of pat in text
int z_algorithm(string text, string pat) {
	auto z = z_function(pat + '\0' + text);

	int res = 0;
	for(int i = 0; i < text.size() - pat.size() + 1; i++)
		if(z[i + pat.size() + 1] == pat.size())
			res++; // occurrence starting at text[i] found

	return res;
}