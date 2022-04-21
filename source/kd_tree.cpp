using T = ll;
using P = Point<T>;

bool cmp_by_x(const P& a, const P& b) { return a.x < b.x; }
bool cmp_by_y(const P& a, const P& b) { return a.y < b.y; }

struct Node {
	P pt;
	T x0 = INF, x1 = -INF, y0 = INF, y1 = -INF;
	Node *first = 0, *second = 0;

	T distance(const P& p) {
		T x = (p.x < x0 ? x0 : p.x > x1 ? x1 : p.x);
		T y = (p.y < y0 ? y0 : p.y > y1 ? y1 : p.y);
		return (P(x,y) - p).dist2();
	}

	Node(vector<P>&& vp) : pt(vp[0]) {
		for (P p : vp) {
			x0 = min(x0, p.x); x1 = max(x1, p.x);
			y0 = min(y0, p.y); y1 = max(y1, p.y);
		}
		if (vp.size() > 1) {
			sort(all(vp), x1 - x0 >= y1 - y0 ? on_x : on_y);
			int half = ssize(vp) / 2;
			first = new Node({vp.begin(), vp.begin() + half});
			second = new Node({vp.begin() + half, vp.end()});
		}
	}
};

struct KDTree {
	Node* root;
	KDTree(const vector<P>& vp) : root(new Node({all(vp)})) {}

	pair<T, P> search(Node *node, const P& p) {
		if (!node->first) {
			// uncomment if we should not find the point itself:
			// if (p == node->pt) return {INF, P()};
			return make_pair((p - node->pt).dist2(), node->pt);
		}
		Node *f = node->first, *s = node->second;
		T bfirst = f->distance(p), bsec = s->distance(p);
		if (bfirst > bsec) swap(bsec, bfirst), swap(f, s);
		auto best = search(f, p);
		if (bsec < best.first)
			best = min(best, search(s, p));
		return best;
	}

	P nearest(const P& p) {
		return search(root, p).second;
	}
};
