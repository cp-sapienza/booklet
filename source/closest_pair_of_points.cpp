using P = Point<ll>;

pair<P, P> closest_pair(vector<P> points) {
	int n = points.size();
	assert(n >= 2);

	auto cmp_by_x = [](const P& a, const P& b) { return tie(a.x, a.y) < tie(b.x, b.y); };
	sort(all(points), cmp_by_x);

	auto cmp_by_y = [](const P& a, const P& b) { return tie(a.y, a.x) < tie(b.y, b.x); };
	set<P, decltype(cmp_by_y)> s(cmp_by_y);
	s.insert(points[0]);
	s.insert(points[1]);

	pair<P, P> res = {points[0], points[1]};
	ll d = (points[0] - points[1]).dist2();

	for (int i = 2, j = 0; i < n; ++i) {
		while ((points[i].x - points[j].x) * (points[i].x - points[j].x) >= d + EPS)
			s.erase(points[j++]);

		P tmp = {0LL, llround(ceill(sqrtl(d) + EPS))};
		auto from = s.upper_bound(points[i] - tmp);
		auto to = s.lower_bound(points[i] + tmp);

		for (auto it = from; it != to; ++it) {
			ll curr = (points[i] - *it).dist2();
			if (curr < d) {
				res.first = points[i];
				res.second = *it;
				d = curr;
			}
		}
		s.insert(points[i]);
	}

	return res;
}
