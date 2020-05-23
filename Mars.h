#ifndef MARS_H
# define MARS_H
# include <vector>
# include "Point.h"
# include "geometry.h"

class Mars
{
private:
	int							pointCount;
	std::vector<Point<double>>	surface;
	double						gravity;
	Point<double>				landP1;
	Point<double>				landP2;
	int							highest;
	double						maxDist;

	Mars& computeLandingZone();

	Mars& computeHighest();

	Mars& computeMaxDist();

public:
	Mars(const double &gravity);

	Mars();

	~Mars() = default;

	const double& getGravity() const;
	const std::vector<Point<double>>& getSurface();

	bool	doCollide(const Point<double>& p1, const Point<double>& p2) const;

	const Point<double>& getLandingP1() const;

	const Point<double>& getLandingP2() const;

	const double& getMaxDist() const;

	const int& getHighest() const;
};

#endif

