#pragma once

template <typename T> class Point;

bool ccw(const Point<double>& p1, const Point<double>& p2, const Point<double>& p3);

bool intersect(const Point<double>& p1, const Point<double>& p2, const Point<double>& p3, const Point<double>& p4);

int orientation(const Point<double>& p, const Point<double>& q, const Point<double>& r);

bool doIntersect(const Point<double>& p1, const Point<double>& q1, const Point<double>& p2, const Point<double>& q2);