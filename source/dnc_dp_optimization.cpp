vector<ll> dp_old, dp_cur;

// Complete this cost function
inline ll cost(int i, int j) {
	return 0LL;
}

void compute(int l, int r, int optl, int optr) {
	if (l > r)
		return;

	int mid = (l + r) >> 1;
	pair<ll, int> best = {LLONG_MAX, -1};

	for (int k = optl; k <= min(mid, optr); ++k)
		best = min(best, {(k ? dp_old[k - 1] : 0) + cost(k, mid), k});

	dp_cur[mid] = best.first;
	int opt = best.second;

	compute(l, mid - 1, optl, opt);
	compute(mid + 1, r, opt, optr);
}
