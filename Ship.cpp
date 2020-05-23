#define _USE_MATH_DEFINES
#include "Ship.h"
#include <cmath>
#include <iostream>
#include "Point.h"
#include "Vec.h"

Ship::Ship()
{
	this->pos = Point<double>(0.0, 0.0); this->vec = Vec<double>(0.0, 0.0); this->fuel = 0; this->rotate = 0; this->power = 0;
}

Ship::Ship(const Point<double>& pos, const Vec<double>& vec, const int& fuel, const int& rotate, const int& power)
{
	this->pos = pos; this->vec = vec; this->fuel = fuel; this->rotate = rotate; this->power = power;
}

Ship& Ship::reset(const Point<double>& pos, const Vec<double>& vec, const int& fuel, const int& rotate, const int& power)
{
	this->pos = pos;
	this->vec = vec;
	this->fuel = fuel; this->rotate = rotate; this->power = power;
	return (*this);
}

Ship& Ship::setRotate(const int& rotate)
{
	this->rotate = rotate;
	return (*this);
}

const Point<double>& Ship::getPos() const
{
	return (this->pos);
}

const Vec<double>& Ship::getVel() const
{
	return (this->vec);
}

const int& Ship::getRotate() const
{
	return (this->rotate);
}

const int& Ship::getPower() const
{
	return (this->power);
}

const int& Ship::getFuel() const
{
	return (this->fuel);
}

Ship& Ship::addRotation(const int& rotate)
{
	this->rotate += rotate;
	if (this->rotate < -90)
		this->rotate = -90;
	else if (this->rotate > 90)
		this->rotate = 90;
	return (*this);
}

Ship& Ship::addPower(const int& power)
{
	this->power += power;
	if (this->power < 0)
		this->power = 0;
	else if (this->power > 4)
		this->power = 4;
	return (*this);
}

Ship& Ship::toNextPosition(const double& gravity, const int& dpower, const int& rotation)
{
	this->addPower(dpower).addRotation(rotation);
	double		rad = (this->rotate * M_PI) / 180;
	double		co = cos(rad);
	double		si = -sin(rad);
	Vec<double>	dvel = Vec(this->power * si, this->power * co + gravity);
	this->pos.add(this->vec.getVx() + 0.5 * dvel.getVx(), this->vec.getVy() + 0.5 * dvel.getVy());
	this->vec += dvel;
	this->fuel -= this->power;
	return (*this);
}