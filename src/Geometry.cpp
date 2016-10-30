#include <iostream>
#include <algorithm>
#include <climits>
#include <time.h>
#include "Geometry.h"

// ---------------------- DIRECTION --------------------------------
// Brief description: define if pk lies from the left or right side
// regarding to pi-pj
// -----------------------------------------------------------------
int Geometry::direction(Point pi, Point pj, Point pk) {
	return ((pk.x - pi.x) * (pj.y - pi.y) - (pj.x - pi.x) * (pk.y - pi.y));
}

// ---------------------- SEGMENTS-INTERSECT -----------------------
// Brief description: find out if 2 segmens p1p2 and p3p4 intersects 
// -----------------------------------------------------------------
bool Geometry::segmentsIntersect(Point p1, Point p2, Point p3, Point p4) {
	int d1 = direction(p3, p4, p1);
	int d2 = direction(p3, p4, p2);
	int d3 = direction(p1, p2, p3);
	int d4 = direction(p1, p2, p4);

	if ((((d1 > 0) && (d2 < 0)) || ((d1 < 0) && (d2 > 0))) &&
		(((d3 > 0) && (d4 < 0)) || ((d3 < 0) && (d4 > 0)))) return true;

}

// ----------------- LAUNCHER -----------------------------
// Brief description: use all available geometry algorithms
// and compare their timings in console output 
// -------------------------------------------------------
void launchAllGeometryAlgorithms() {
	//-------------------------------------------------
	Point p1 = { 0, 0 }; Point p2 = { 2, 0 };
	Point p3 = { 1, 1 }; Point p4 = { 1, -1 };

	auto isStart = clock();
	bool isIntersect = Geometry::segmentsIntersect(p1, p2, p3, p4);
	auto isEnd = clock() - isStart;
	std::cout << "Segments intersection: " << isEnd << " ms" << std::endl;

	bool check = isIntersect;
	
	if (check) std::cout << "All geometry algorithms are correct" << std::endl << std::endl;
	else std::cout << "Error!" << std::endl << std::endl;
}