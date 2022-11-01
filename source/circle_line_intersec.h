#pragma once
#include "common.h"
#include "line.h"



vector<Point<ld>> circle_x_line(ld rad, Line ln, Point<ld> center = {0, 0}){
	ln = ln + (-center);
	Point<ld> o(0, 0);
	Point<ld> p0 = closest_point(o, ln);
	ld t = ln.a*ln.a+ln.b*ln.b;

	if (ln.c*ln.c > rad*rad*t+EPS)
		return {};
	if (abs(ln.c*ln.c - rad*rad*t) < EPS) {
		return {p0+center};
	}

	ld d = rad*rad - ln.c*ln.c/t;
	ld mult = sqrtl(d/t);
	Point vec(ln.b, -ln.a);
	return {p0+vec*mult+center, p0-vec*mult+center};
}