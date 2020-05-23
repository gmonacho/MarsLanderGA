#include "Population.h"
#include <algorithm>
#include <iostream>
#include "Mars.h"

Population::Population(const Ship& startShip)
{
	this->currPop = this->group1;
	this->nextPop = this->group2;
	this->solution = nullptr;
	this->startShip = startShip;
}

Population& Population::nextGeneration(const Mars& mars, Point<double>** dispPop)
{
	this->computeMarks(mars, dispPop);
	this->checkSolution(mars);
	this->rouletteWheel();
	this->generateNewPop();
	this->swapPops();
	return (*this);
}

bool Population::solutionFound() const
{
	return (this->solution);
}

Population& Population::checkSolution(const Mars& mars)
{
	const Point<double>& p1 = mars.getLandingP1();
	const Point<double>& p2 = mars.getLandingP2();

	for (int i = 0; i < POP; i++)
	{
		if (this->currPop[i].isSolution(mars, 20, 40, 0))
		{
			this->solution = &this->currPop[i];
			break;
		}
	}
	return (*this);
}

Population& Population::swapPops()
{
	std::swap(currPop, nextPop);
	return (*this);
}

Population& Population::sortPop()
{
	for (int i = 0; i < POP; i++)
	{
		for (int j = i + 1; j < POP; j++)
		{
			if (this->currPop[i].getMark() < this->currPop[j].getMark())
			{
				std::swap(this->currPop[i], this->currPop[j]);
				break;
			}
		}
	}
	return (*this);
}

double Population::getMarkSum() const
{
	double	mark = 0;
	for (int i = 0; i < POP; i++)
		mark += currPop[i].getMark();
	return (mark);
}

Population& Population::normPop(const double& sum)
{
	for (int i = 0; i < POP; i++)
		currPop[i].normMark(sum);
	return (*this);
}

Population& Population::computeCumulativeSum()
{
	for (unsigned int i = 0; i < POP; i++)
	{
		double mark = 0;
		for (unsigned int j = i; j < POP; j++)
			mark += this->currPop[j].getMark();
		this->currPop[i].setMark(mark);
	}
	return (*this);
}

const Individual& Population::getCandidate() const
{
	double rand_indice = (rand() % 1000) / 1000.0;
	unsigned int i = 0;
	while (i < POP && this->currPop[i].getMark() > rand_indice)
		i++;
	if (i > 0)
		i -= 1;
	return (this->currPop[i]);
}

int Population::getAverageVx() const
{
	double	sum{ 0 };
	int		n{ 0 };

	for (int i = 0; i < POP; i++)
	{
		const Ship& ship = this->currPop[i].getShip();
		sum += ship.getVel().getVx();
		n++;
	}
	return (sum / n);
}


int Population::getAverageVy() const
{
	double	sum{ 0 };
	int		n{ 0 };

	for (int i = 0; i < POP; i++)
	{
		const Ship& ship = this->currPop[i].getShip();
		sum += ship.getVel().getVy();
		n++;
	}
	return (sum / n);
}

int Population::getAverageRotation() const
{
	double	sum{ 0 };
	int		n{ 0 };

	for (int i = 0; i < POP; i++)
	{
		const Ship& ship = this->currPop[i].getShip();
		sum += ship.getRotate();
		n++;
	}
	return (sum / n);
}

Individual* Population::getSolution()
{
	return (this->solution);
}

Population& Population::generateNewPop()
{
	int elitCount = POP * (15 / 100.0);
	if (elitCount % 2 == 1)
		elitCount++;
	for (int i = 0; i < elitCount; i++)
		this->nextPop[i] = this->currPop[i];
	for (unsigned int i = elitCount; i < POP; i++)
	{
		const Individual& parent1 = this->getCandidate();
		const Individual& parent2 = this->getCandidate();
		
		double random = (std::rand() % 1000) / 999;

		this->nextPop[i++].continuousBorn(parent1, parent2, random);
		this->nextPop[i].continuousBorn(parent2, parent1, random);

		//this->nextPop[i].born(parent1, parent2);
	}
	return (*this);
}

Population& Population::rouletteWheel()
{
	this->normPop(this->getMarkSum());
	this->sortPop();
	this->computeCumulativeSum();
	return (*this);
}

Population& Population::computeMarks(const Mars& mars, Point<double>** dispPop)
{
	for (int  i = 0; i < POP; i++)
		this->currPop[i].computeLastPos(mars, (dispPop) ? dispPop[i++] : nullptr, this->startShip);
	return (*this);
}
