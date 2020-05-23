#include "Mars.h"
#include <iostream>
#include "Point.h"
#define MAP_X 7000
#define MAP_Y 3000

Mars& Mars::computeLandingZone()
{
	Point<double>	land1 = this->surface[0];
	Point<double> 	land2;
	int	i = 1;

	while (i < this->pointCount)
	{
		land2 = this->surface[i];
		if (land1.getY() == land2.getY())
			break;
		land1 = land2;
		i++;
	}
	this->landP1 = land1;
	this->landP2 = land2;
	return (*this);
}

Mars& Mars::computeHighest()
{
	this->highest = -1;

	for (int i = 0; i < this->pointCount; i++)
	{
		if (this->surface[i].getY() > this->highest || highest == -1)
			this->highest = this->surface[i].getY();
	}
	return (*this);
}

Mars& Mars::computeMaxDist()
{
	this->maxDist = 2 * std::sqrt(MAP_X * MAP_X + MAP_Y * MAP_Y);
	return (*this);
}

Mars::Mars(const double& gravity)
{
	std::cin >> this->pointCount; std::cin.ignore();
	this->surface.reserve(this->pointCount);
	for (int i = 0; i < this->pointCount; i++)
	{
		int landX;
		int landY;

		std::cin >> landX >> landY; std::cin.ignore();
		this->surface.push_back(Point<double>(landX, landY));
	}
	this->gravity = gravity;
	this->computeMaxDist();
	this->computeLandingZone();
	this->computeHighest();
}

Mars::Mars()
{
	// easy on right
	//this->surface = std::vector<Point<double>>({ Point<double>(0, 100),
	//	Point<double>(1000, 500),
	//	Point<double>(1500, 1500),
	//	Point<double>(3000, 1000),
	//	Point<double>(4000, 150),
	//	Point<double>(5500, 150),
	//	Point<double>(6999, 800) });
	
	// 2
	//this->surface = std::vector<Point<double>>({ Point<double>(0, 100),
	//	Point<double>(1000, 500),
	//	Point<double>(1500, 100),
	//	Point<double>(3000, 100),
	//	Point<double>(3500, 500),
	//	Point<double>(3700, 200),
	//	Point<double>(5000, 1500),
	//	Point<double>(5800, 300),
	//	Point<double>(6000, 1000),
	//	Point<double>(6999, 2000) });

	 //3
	this->surface = std::vector<Point<double>>({ Point<double>(0, 100),
		Point<double>(1000, 500),
		Point<double>(1500, 1500),
		Point<double>(3000, 1000),
		Point<double>(4000, 150),
		Point<double>(5500, 150),
		Point<double>(6999, 800) });

	//4
	//this->surface = std::vector<Point<double>>({ Point<double>(0, 1000),
	//	Point<double>(300, 1500),
	//	Point<double>(350, 1400),
	//	Point<double>(500, 2000),
	//	Point<double>(800, 1800),
	//	Point<double>(1000, 2500),
	//	Point<double>(1200, 2100),
	//	Point<double>(1500, 2400),
	//	Point<double>(2000, 1000),
	//	Point<double>(2200, 500),
	//	Point<double>(2500, 100),
	//	Point<double>(2900, 800),
	//	Point<double>(3000, 500),
	//	Point<double>(3200, 1000),
	//	Point<double>(3500, 2000),
	//	Point<double>(3800, 800),
	//	Point<double>(4000, 200),
	//	Point<double>(5000, 200),
	//	Point<double>(5500, 1500),
	//	Point<double>(6999, 2800) });

	//this->surface = std::vector<Point<double>>({
	//Point<double>(0, 1000),
	//Point<double>(300, 1500),
	//Point<double>(350, 1400),
	//Point<double>(500, 2100),
	//Point<double>(1500, 2100),
	//Point<double>(2000, 200),
	//Point<double>(2500, 500),
	//Point<double>(2900, 300),
	//Point<double>(3000, 200),
	//Point<double>(3200, 1000),
	//Point<double>(3500, 500),
	//Point<double>(3800, 800),
	//Point<double>(4000, 200),
	//Point<double>(4200, 800),
	//Point<double>(4800, 600),
	//Point<double>(5000, 1200),
	//Point<double>(5500, 900),
	//Point<double>(6000, 500),
	//Point<double>(6500, 300),
	//Point<double>(6999, 500)});
	this->gravity = -3.711;
	this->pointCount = this->surface.size();
	this->computeMaxDist();
	this->computeLandingZone();
	this->computeHighest();
}

const double &Mars::getGravity() const
{
	return (this->gravity);
}

const std::vector<Point<double>>& Mars::getSurface()
{
	return (this->surface);
}

bool Mars::doCollide(const Point<double>& p1, const Point<double>& p2) const
{
	Point<double>		land1 = this->surface[0];
	Point<double>		land2;

	for (int i = 1; i < this->pointCount; i++)
	{
		land2 = this->surface[i];
		if (intersect(p1, p2, land1, land2))
			return (true);
		land1 = land2;
	}
	return (false);
}

const Point<double>& Mars::getLandingP1() const
{
	return (this->landP1);
}

const Point<double>& Mars::getLandingP2() const
{
	return (this->landP2);
}

const double& Mars::getMaxDist() const
{
	return (this->maxDist);
}

const int& Mars::getHighest() const
{
	return (this->highest);
}
