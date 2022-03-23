bool cmp(Node nd, int k) {
	return nd.field >= k;  // condition we want on result of lower_bound(k)
}
int lower_bound(int k)
{
	if(!cmp(st[1], k))
		return -1;
	int p = 1;
	Node part = unit;
	while(p<n_po2)
	{
		p <<= 1;
		if(!cmp(merge(part, st[p]), k)) {
			part = merge(part, st[p++]);
		}
	}
	return p-n;
}
