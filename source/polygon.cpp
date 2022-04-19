ld perimeter(vector<Point<ll>>& poli){
    ld res = 0.0;
    int n = ssize(poli);
    for(int i = 1; i <= n; ++i) res += poli[(i-1) % n].dist(poli[(i)%n]);
    return res;
}

// returns 2*area; area < 0 if clock-wise, area > 0 if ccw
ll double_area(vector<Point<ll>>& poli){
    ll res = 0.0;
    int n = ssize(poli);
    for(int i = 0; i < n; ++i)
        res += (poli[(i)%n].x * poli[(i+1)%n].y - poli[(i+1)%n].x*poli[(i)%n].y);
    return res;
}

bool check_convex(vector<Point<ll>>& poli){
    int n = ssize(poli);
    if(n < 3) return false;
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
    if(n < 3) return -1;
    bool on_polygon = false;
    ld sum = 0.0;
    for(int i = 0; i < n; i++){
        if(pt == poli[(i)%n] || pt == poli[(i+1)%n] || pt.collinear(poli[(i)%n], poli[(i+1)%n])){ //on_segment invece di collinear
            return 0;
        }
        if(poli[(i+1)%n].ccw_check(pt, poli[i%n])) sum += poli[i].aob_angle(pt, poli[(i+1)%n]);
        else sum -= poli[i].aob_angle(pt, poli[i+1]);
    }
    return abs(sum) > M_PI ? 1 : -1;
}




