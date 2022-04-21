ld perimeter(vector<Point<ll>>& poli){
	ld res = 0.0;
	int n = ssize(poli);
	for(int i = 1; i <= n; ++i) res += poli[i-1].dist(poli[i % n]);
	return res;
}
// returns 2*area; area < 0 if clock-wise, area > 0 if ccw
ll double_area(vector<Point<ll>>& poli){
	ll res = 0;
	int n = ssize(poli);
	for(int i = 0; i < n; ++i)
		res += (poli[i % n].x * poli[(i+1)%n].y - poli[(i+1)%n].x*poli[i % n].y);
	return res;
}
bool check_convex(vector<Point<ll>>& poli){
	int n = ssize(poli);
	if(n < 3) return true;
	bool ft = poli[2].ccw_check(poli[0], poli[1]);
	for(int i = 1; i < n-1; ++i)
		if((poli[(i+2)%n]).ccw_check(poli[i%n], poli[(i+1)%n]) != ft){
			return false; // concave
		}
	return true; // convex
}
// returns 1/0/-1 if pt inside/on vertex or edge/outside poli
int point_inside_polygon(Point<ll> pt, vector<Point<ll>>& poli){
	int n = ssize(poli);
	if(n == 1) return (pt == poli[0]) ? 0 : -1;
	if(n == 2) return pt.on_segment(poli[0], poli[1]) ? 0 : -1;
	bool on_polygon = false;
	ld sum = 0.0;
	for(int i = 0; i < n; i++){
		if(pt == poli[i] || pt == poli[(i+1)%n] || pt.on_segment(poli[i], poli[(i+1)%n])){
			return 0;
		}
		if(poli[(i+1)%n].ccw_check(pt, poli[i])) sum += poli[i].aob_angle(pt, poli[(i+1)%n]);
		else sum -= poli[i].aob_angle(pt, poli[(i+1)%n]);
	}
	return abs(sum) > M_PI ? 1 : -1;
}
ld dist_point_segment(Point<ll> p, Point<ll> a, Point<ll> b){
	Line l(a, b);
	Point<ld> c = closest_point(p, l);
	Point<ld> pld = p.to_ld();
	if(c.x >= min(a.x, b.x) && c.x <= max(a.x, b.x) && c.y >= min(a.y, b.y) && c.y <= max(a.y, b.y)){
		return pld.dist(c);

	}
	ld dap = pld.dist(a.to_ld()), dbp = pld.dist(b.to_ld());
	if(dap - dbp < EPS) return dap;
	else return dbp;
}
// distance from pt to the closest side of the polygon
ld dist_point_poly(Point<ll> pt, vector<Point<ll>>& poli){
	ld best_dist = numeric_limits<ld>::max();
	int n = ssize(poli);
	for(int i = 0; i <= n; i++){
		best_dist = min(best_dist, dist_point_segment(pt, poli[i%n], poli[(i+1)%n]));
	}
	return best_dist;
}
// Returns the left subspace wrt AB
// for the one on the right, call cut_poly with A, B and all vertices in Q
// with the x negated and then negate the x of the result
vector<Point<ld>> cut_poly(Point<ld> A, Point<ld> B, const vector<Point<ld>> &Q) {
  vector<Point<ld>> P;
  int n = ssize(Q);
  for (int i = 0; i < n; i++) {
	ld left1 = (B-A).cross(Q[i] - A), left2 = 0;
	if (i != n-1) left2 = (B-A).cross(Q[(i+1)%n] - A);
	if (left1 > -EPS) P.push_back(Q[i%n]);
	if (left1*left2 < -EPS)
	  P.push_back(intersec_line_seg(Q[i], Q[(i+1)%n], A, B));
  }
  return P;
}
