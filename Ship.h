#ifndef SHIP_H
# define SHIP_H
# include "Vec.h"
# include "Point.h"

class Ship
{
private:
	Point<double> pos;
	Vec<double> vec;
	int fuel;
	int rotate;
	int	power;

public:
	Ship();
	Ship(const Point<double>& pos, const Vec<double>& vec, const int& fuel, const int& rotate, const int& power);
	~Ship() = default;

	Ship& reset(const Point<double>& pos, const Vec<double>& vec, const int& fuel, const int& rotate, const int& power);
	
	Ship& setRotate(const int& rotate);
	Ship& setVelocity(const double& vx, const double& vy);

	const Point<double>& getPos() const;
	const Vec<double>& getVel() const;
	const int& getRotate() const;
	const int& getPower() const;
	const int& getFuel() const;

	Ship& addRotation(const int& rotate);
	Ship& addPower(const int& power);

	Ship& toNextPosition(const double& gravity, const int& dpower, const int& rotation);
};

#endif