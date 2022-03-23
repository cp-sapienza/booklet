int lower_bound(Value k) {
	int t, res = 0;
	t = 1 << (__builtin_clz(1)-__builtin_clz(ssize(ft)));
	while(t) {
		if(t+res<ssize(ft)-1 && ft[t+res]<k) {
		//                               ^<= for upper_bound
			res += t;
			k -= ft[res];
		}
		t /= 2;
	}
	return ft[res+1]<k? -1:res;
}
