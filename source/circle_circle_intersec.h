#pragma once
#include "circle_line_intersec.h"


vector<Point<ld>> circle_x_circle(Point<ld> c1, ld rad1, Point<ld> c2, ld rad2) {
//	assert(!(c1 == c2));
	c2 = c2 - c1;
	auto t = circle_x_line(rad1, norm(-2*c2.x, -2*c2.y, c2.dist2()+rad1*rad1-rad2*rad2));
	for(auto &p:t)
		p = p+c1;
	return t;
}
