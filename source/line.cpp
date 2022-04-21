struct Line{
	ld a, b, c; // b = 1 non-vertical lines, b = 0 vertical lines
	Line(ld a_, ld b_, ld c_) : a(a_), b(b_), c(c_) {}
	Line(Point<ll>& p1, Point<ll>& p2){
		if(abs(p1.x - p2.x) < EPS){
			a = 1.0; b = 0.0; c = -p1.x;
		}
		else{
			a = -(ld)(p1.y - p2.y) / (p1.x - p2.x);
			b =  1.0;
			c = -(ld) (a * p1.x) - p1.y;
		}
	}
	Line(Point<ll>& p, ld m){
		a = m; b = 1.0; c = -((a * p.x) + (b * p.y));}
	bool check_parallel(Line l){
		return (abs(a-l.a) < EPS) && (abs(b-l.b) < EPS);}
	bool check_same(Line l) {                
		return this -> check_parallel(l) && (abs(c-l.c) < EPS);}
	bool check_orthogonal(Line l){
		return abs(a + 1/l.a) < EPS;}
	bool check_intersection(Line l, Point<ld>& p){ // if true, P is the intersection point
		if(this -> check_parallel(l)) return false;
		p.x = (l.b * c - b * l.c) / (l.a * b - a * l.b);
		if(abs(b) > EPS) p.y = -(a * p.x + c);
		else p.y = -(l.a * p.x + c);
		return true;
	}
	friend ostream& operator<<(ostream& os, Line l) {
		return os << "(" << l.a << ", " << l.b  << ", " << l.c <<")"; }
};
ld dist_to_line(Point<ll> p, Line l){
	return abs(l.a * p.x + l.b * p.y + l.c) / sqrt(l.a * l.a + l.b * l.b);}
Point<ld> closest_point(Point<ll> p, Line l) { // returns the closest point to p on l 
  Point<ld> ans;                         
  if (abs(l.b) < EPS) {                         
	ans.x = -(l.c);
	ans.y = p.y;
	return ans;
  }
  if (abs(l.a) < EPS) {                        
	ans.x = p.x;
	ans.y = -(l.c);
	return ans;
  }
  Line perpendicular = Line(p, -1/l.a);
  l.check_intersection(perpendicular, ans);
  return ans;
}
// returns intersection point between line AB and segment pq
Point<ld> intersec_line_seg(Point<ld> p, Point<ld> q, Point<ld> A, Point<ld> B){
	ld a = B.y - A.y, b = A.x - B.x, c = B.x * A.y - A.x * B.y;
	ld u = abs(a*p.x + b*p.y + c);
	ld v = abs(a*q.x + b*q.y + c);
	return Point<ld>((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
}