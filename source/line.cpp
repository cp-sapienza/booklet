struct Line{
    ld a, b, c; // b = 1 linee non verticali, 0 Linee verticali
    Line(ld a_, ld b_, ld c_) : a(a_), b(b_), c(c_) {}
    Line(Point<ll>& p1, Point<ll>& p2){
        if(fabs(p1.x - p2.x) < EPS){
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
        return (fabs(a-l.a) < EPS) && (fabs(b-l.b) < EPS);}
    bool check_same(Line l) {                
        return this -> check_parallel(l) && (fabs(c-l.c) < EPS);}
    bool check_orthogonal(Line l){ // m1 = -1/m2, m = a / (-b)
        ld diff = fabs(a) - fabs(1/l.a); return (diff < EPS);}
    bool check_intersection(Line l, Point<ld>& p){ // if true, P is the intersection point
        if(this -> check_parallel(l)) return false;
        p.x = (l.b * c - b * l.c) / (l.a * b - a * l.b);
        if(fabs(b) > EPS) p.y = -(a * p.x + c);
        else p.y = -(l.a * p.x + c);
        return true;
    }
    friend ostream& operator<<(ostream& os, Line l) {
		return os << "(" << l.a << ", " << l.b  << ", " << l.c <<")"; }
};
ld dist_to_line(Point<ll> p, Line l){
    return fabs(l.a * p.x + l.b * p.y + l.c) / sqrt(l.a * l.a + l.b * l.b);
}
Point<ld> closest_point(Point<ll> p, Line l) { // ritorna il punto più vicino a p su l
  Point<ld> ans;                         
  if (fabs(l.b) < EPS) {                         
    ans.x = -(l.c);
    ans.y = p.y;
    return ans;
  }
  if (fabs(l.a) < EPS) {                        
    ans.x = p.x;
    ans.y = -(l.c);
    return ans;
  }
  Line perpendicular = Line(p, -1/l.a);
  l.check_intersection(perpendicular, ans);
  return ans;
}
