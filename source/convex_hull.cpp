using P = Point<ll>;

vector<P> convex_hull(vector<P> points, bool collinear_edges=false) {
	vector<P> hull;
	sort(all(points), [](const P& a, const P& b){ return tie(a.x, a.y) < tie(b.x, b.y); });
	for (int _ = 0; _ < 2; ++_) {
		int sz = hull.size();
		for (P& p : points) {
			if (ssize(hull) && hull.end()[-1] == p) continue;
			while (ssize(hull) - sz >= 2) {
				auto x = hull.end()[-2].cross(hull.end()[-1], p);
				if (x < 0 || (collinear_edges && x == 0)) break;
				hull.pop_back();
			}
			hull.push_back(p);
		}
		if (ssize(hull) == 1) return hull;
		hull.pop_back();
		reverse(all(points));
	}
	reverse(all(hull));
	return hull;
}
