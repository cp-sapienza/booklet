#pragma once
#include "common.h"

vi pi_function(string s) {
	int n = ssize(s);
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
	for(int i = 0, j = 0; i < ssize(text); i++) {
		while(j > 0 && text[i] != pat[j]) j = pi[j-1];
		if(text[i] == pat[j]) ++j;
		if(j == ssize(pat))
			res++; // occurrence starting at text[i-pat.size()+1] found
	}
	return res;
}