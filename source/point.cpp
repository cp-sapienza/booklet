ld deg_to_rad(ld d) { return d * PI / 180.0; }
ld rad_to_deg(ld r) { return r * 180.0 / PI; }

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x+y*y; }
	ld dist(P from = {0, 0}) const { return sqrt((ld)(*this-from).dist2());}\
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	// angle with custom center o in interval [0, pi]
	ld aob_angle(P o, P b) { 
		return acos((*this-o).dot(b-o) / sqrt((*this-o).dist2() * (b-o).dist2()));}
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point p rotated ccw of theta degrees wrt center c
	// clockwise rotation: use -theta, center = c
	P ccw_rotation(const P& p, ld theta, const P c = P(0, 0)){
        ld rad = deg_to_rad(theta);
        return point(cos(rad) * (p.x - c.x) - sin(rad) * (p.y - c.y) + c.x, sin(rad) * (p.x - c.x) - cos(rad) * (p.y - c.y) + c.y);}
    bool collinear(P q, P r){return abs(this -> cross(q, r)) < EPS;}
    bool ccw_check(P p, P q) { // returns true if the point is on the left side of line pq
        return (q-p).cross((*this)-p) > 0;}
	bool on_segment(P A, P B){ // returns true if this is on segment AB
		if(this -> collinear(A, B) && this -> x <= max(A.x, B.x) && this -> x >= min(A.x, B.x)
			&& this -> y <= max(A.y, B.y) && this -> y >= min(A.y, B.y)) return true;
		else return false;
	}
	Point<ld> to_ld(){
		Point<ld> ldp((ld)(this -> x), (ld)(this -> y));
		return ldp;
	}
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << ", " << p.y << ")"; }
};

