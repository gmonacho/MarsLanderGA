#include "geometry.h"
#include "Point.h"

bool ccw(const Point<double>& p1, const Point<double>& p2, const Point<double>& p3)
{
	return ((p3.getY() - p1.getY()) * (p2.getX() - p1.getX()) > (p2.getY() - p1.getY()) * (p3.getX() - p1.getX()));
}

bool intersect(const Point<double>& p1, const Point<double>& p2, const Point<double>& p3, const Point<double>& p4)
{
	return (ccw(p1, p3, p4) != ccw(p2, p3, p4) && ccw(p1, p2, p3) != ccw(p1, p2, p4));
}

int orientation(const Point<double>& p, const Point<double>& q, const Point<double>& r)
{
    int val = ((int)q.getY() - (int)p.getY()) * ((int)r.getX() - (int)q.getX()) -
        ((int)q.getX() - (int)p.getX()) * ((int)r.getY() - (int)q.getY());

    if (val == 0) return 0;

    return (val > 0) ? 1 : 2; 
}

bool doIntersect(const Point<double>& p1, const Point<double>& q1, const Point<double>& p2, const Point<double>& q2)
{
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case 
    if (o1 != o2 && o3 != o4)
        return (true);
    else
        return (false);
    
}