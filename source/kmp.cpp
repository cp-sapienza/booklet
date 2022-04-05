vi pi_function(string s) {
	int n = s.size();
	vi pi(n, 0);
	for(int i = 1, j = 0; i < n; i++) {
		while(j > 0 && s[i] != s[j]) j = pi[j-1];
		if(s[i] == s[j]) pi[i] = ++j;
	}
	return pi;
}

// Find occurrences of pat in text
int kmp(string text, string pat) {
	auto pi = pi_function(pat);

	int res = 0;
	for(int i = 0, j = 0; i < text.size(); i++) {
		while(j > 0 && text[i] != pat[j]) j = pi[j-1];
		if(text[i] == pat[j]) ++j;
		if(j == pat.size())
			res++; // occurrence starting at text[i-pat.size()+1] found
	}
	return res;
}