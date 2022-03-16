struct MoQuery {
	int x, y, idx; // [x, y]
	static const int block_size = 450; // should be ~sqrt(MAXN)
	bool operator<(const MoQuery& rhs) const {
		if(x / block_size != rhs.x / block_size)
			return x / block_size < rhs.x / block_size;
		if(x / block_size & 1) return y < rhs.y;
		return y > rhs.y;
	}
};

auto mo_queries(vector<MoQuery>& queries) {
	// Fill these in
	auto add = [&](int idx) {};
	auto remove = [&](int idx) {};
	auto getresult = [&]() { return 0; };

	sort(all(queries));
	int left = 0, right = -1;
	vector<int> result(queries.size());

	for(auto& query : queries) {
		while(left > query.x) left--, add(left);
		while(left < query.x) remove(left), left++;
		while(right > query.y) remove(right), right--;
		while(right < query.y) right++, add(right);
		result[query.idx] = getresult();
	}
	return result;
}