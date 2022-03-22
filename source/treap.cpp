mt19937 rng{42};

struct Treap {
	using Val = int;

	Val val; // Node value
	ll sum; // Query result on subtree
	bool rev; // Lazy operation to push

	int prio, sz;
	Treap *left, *right;

	Treap(Val x, Treap* l = NULL, Treap *r = NULL) {
		val = x; sz = 1; prio = rng();
		left = l; right = r; rev = false; sum = 0;
	}
	~Treap() {
		if(left) delete left;
		if(right) delete right;
	}
	void recalc() {
		sz = 1;
		sum = val;
		if(left) sz += left->sz, sum += left->sum;
		if(right) sz += right->sz, sum += right->sum;
	}
	void push() {
		if(rev) {
			swap(left, right);
			if(left) left->rev ^= 1;
			if(right) right->rev ^= 1;
		}
		rev = false;
	}
};

// pos: sz of left tree
pair<Treap*,Treap*> split(Treap* u, int pos) {
	if(!u) return {NULL, NULL};
	u->push();
	Treap *t;
	int ls = u->left ? u->left->sz : 0;
	if(ls >= pos) {
		tie(t, u->left) = split(u->left, pos);
		u->recalc();
		return {t, u};
	} else {
		tie(u->right, t) = split(u->right, pos-ls-1);
		u->recalc();
		return {u, t};
	}
}
Treap *merge(Treap* left, Treap* right) {
	if(!left) return right;
	if(!right) return left;
	left->push(); right->push();
	if(left->prio < right->prio) {
		left->right = merge(left->right, right);
		left->recalc();
		return left;
	} else {
		right->left = merge(left, right->left);
		right->recalc();
		return right;
	}
}
Treap *insert(Treap* u, int pos, Treap::Val v) {
	if(u) u->push();
	auto [l, r] = split(u, pos);
	return merge(l, merge(new Treap(v), r));
}
// If val is provided, it stores the deleted value
Treap* erase(Treap* u, int pos, Treap::Val *val = NULL) {
	if(u) u->push();
	auto [l, r] = split(u, pos);
	auto [r1, r2] = split(r, 1);
	if(val) *val = r1->val;
	delete r1;
	return merge(l, r2);
}
Treap::Val find(Treap *u, int pos) {
	if(!u) return -1; // pos out of bounds
	u->push();
	int ls = u->left ? u->left->sz : 0;
	if(ls > pos) return find(u->left, pos);
	if(ls < pos) return find(u->right, pos-ls-1);
	return u->val;
}
// Perform some operation op on range [a,b]
template<typename Op>
Treap *range_operation(Treap *u, int a, int b, Op op) {
	auto [l,mr] = split(u, a);
	auto [m,r] = split(mr, b-a+1);
	op(m);
	return merge(l, merge(m, r));
}
// Execute op on each node, from left to right
template<typename Op>
void visit(Treap *u, Op op) {
	if(!u) return;
	u->push();
	visit(u->left, op);
	op(u);
	visit(u->right, op);
}