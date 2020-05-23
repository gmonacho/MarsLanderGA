#include "Individual.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Point.h"
#include "Mars.h"

Individual::Individual()
{
	this->mark = 0;
}

Individual& Individual::operator+=(const Individual& other)
{
	this->mark += other.mark;
	return (*this);
}

const double& Individual::getMark() const
{
	return (this->mark);
}

Individual& Individual::setStartShip(const Ship &startShip)
{
	this->ship = startShip;
	return (*this);
}

const Ship& Individual::getShip() const
{
	return (this->ship);
}

#include <iostream>
Individual& Individual::computeMark(const Mars& mars)
{
	const Point<double>& p1 = mars.getLandingP1();
	const Point<double>& p2 = mars.getLandingP2();
	const Point<double>& shipPos = this->ship.getPos();
	const Point<double>& closest = (std::abs(p1.getX() - shipPos.getX()) < std::abs(p2.getX() - shipPos.getX())) ? p1 : p2;

	if (shipPos.isXBetween(p1.getX(), p2.getX()))
	{
		this->mark = 200;
		if (std::abs(this->ship.getVel().getVx()) > 20)
			this->mark -= (std::abs(this->ship.getVel().getVx()) - 20) / 2.0;
		//std::cerr << '\n' <<"mark = " << this->mark << " vx = " << this->ship.getVel().getVx() << std::endl;
		if (std::abs(this->ship.getVel().getVy()) > 40)
			this->mark -= (std::abs(this->ship.getVel().getVy()) - 40) / 2.0;
		//std::cerr << "mark = " << this->mark << " vy = " << this->ship.getVel().getVy() << std::endl;
		//if (abs(this->ship.getRotate() > 15))
		//	this->mark -= abs(this->ship.getRotate()) - 15;
		this->mark -= std::abs(this->ship.getRotate() / 2.0);
		//std::cerr << "mark = " << this->mark << " rotate = " << this->ship.getRotate() << std::endl;
	}
	else
	{
		//this->mark = 100 / std::sqrt(std::pow(closest.getX() - shipPos.getX(), 2) + std::pow(closest.getY() - shipPos.getY(), 2));
		this->mark = 100 - (100 * std::sqrt(std::pow(closest.getX() - shipPos.getX(), 2) + std::pow(closest.getY() - shipPos.getY(), 2)) / mars.getMaxDist());
		//std::cerr << "mark = " << this->mark << std::endl;
	}
	if (this->mark > 1)
		this->mark = std::pow(this->mark, 3);
	return (*this);
}

Individual& Individual::computeLastPos(const Mars& mars, Point<double>* dispPop, const Ship& startShip)
{
	this->ship.reset(startShip.getPos(), startShip.getVel(), startShip.getFuel(), startShip.getRotate(), startShip.getPower());
	int	rotations[GENES];
	int i = 0;
	while (i < GENES)
	{
		rotations[i] = this->ship.getRotate();
		Point<double>	lastPos = this->ship.getPos();
		int				lastRotation = this->ship.getRotate();
		 if (dispPop)
		 	dispPop[i] = lastPos;
		this->ship.toNextPosition(mars.getGravity(), this->genes[i].getPower(), this->genes[i].getRotation());
		if (this->ship.getPos().getX() < 0 || this->ship.getPos().getX() > MAP_X || (this->ship.getPos().getY() <= mars.getHighest() && mars.doCollide(lastPos, this->ship.getPos())))
		{
			this->genes[i - 1].setRotation(-rotations[i - 1]);
			rotations[i] = rotations[i - 1] + this->genes[i - 1].getRotation();
			this->genes[i].setRotation(0);
			this->ship.setRotate(rotations[i]);
			break;
		}
		i++;
	}
	if (dispPop)
	{
		dispPop[i++] = this->ship.getPos();
		while (i < GENES)
			dispPop[i++].setX(0);
	}
	this->computeMark(mars);
	return (*this);
}

Individual& Individual::setMark(const double& mark)
{
	this->mark = mark;
	return (*this);
}


Individual& Individual::normMark(const double & sum)
{
	this->mark /= sum;
	return (*this);
}

Individual& Individual::continuousBorn(const Individual& parent1, const Individual& parent2, const double& crossRate)
{
	for (unsigned int i = 0; i < GENES; i++)
	{
		int r = std::rand() % 100;
		if (r < 1)
			this->genes[i].mutate();
		else
			this->genes[i].evolve(parent1.genes[i], parent2.genes[i], crossRate);
			//else if (r == 10)
		//	this->genes[i].hardMutate();
	}
	return (*this);
}

Individual& Individual::born(const Individual& parent1, const Individual& parent2)
{
	int index = std::rand() % GENES;
	for (int i = 0; i < index; i++)
	{
		this->genes[i] = parent1.genes[i];
		if (std::rand() % 100 < 1)
			this->genes[i].mutate();
	}
	for (int i = index; i < GENES; i++)
	{
		this->genes[i] = parent2.genes[i];
		if (std::rand() % 100 < 1)
			this->genes[i].mutate();
	}
	return (*this);
}

bool Individual::isSolution(const Mars& mars, const unsigned int& vx, const unsigned int& vy, const unsigned int& minFuel)
{
	return (this->ship.getPos().isXBetween(mars.getLandingP1().getX(), mars.getLandingP2().getX())
		&& std::abs(this->ship.getVel().getVx()) <= vx
		&& std::abs(this->ship.getVel().getVy()) <= vy
		&& this->ship.getFuel() >= minFuel);
}
