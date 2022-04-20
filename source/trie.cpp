struct Trie { 
	struct Node {
		bool marker = false;
		int next[26];
		Node() { for (int& x : next) x = -1; }
	};

	int toidx(char ch) { return ch - 'a'; }
	int root() { return 0; }
	bool marker(int u) { return v[u].marker; }

	vector<Node> v = {Node()};

	void insert(const string& s) {
		int u = 0;
		for (char ch : s) {
			if (v[u].next[toidx(ch)] == -1)
				v[u].next[toidx(ch)] = v.size(), v.emplace_back();
			u = v[u].next[toidx(ch)];
		}
		v[u].marker = true;
	}

	bool find(const string& s) {
		int u = 0;
		for (char ch : s)
			if (!move(u, ch)) return false;
		return marker(u);
	}

	bool move(int& u, char ch) {
		if (v[u].next[toidx(ch)] == -1) return false;
		u = v[u].next[toidx(ch)];
		return true;
	}
};
