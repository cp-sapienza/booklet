struct Node {
	ll h, p;
	Node(char ch) { h = ch; p = 26; }
	Node() { h = 0; p = 1; }
};

Node unit;
Node merge(Node& a, Node& b) {
	Node res;
	res.p = (a.p * b.p) % mod;
	res.h = (a.h * b.p + b.h) % mod;
	return res;
}