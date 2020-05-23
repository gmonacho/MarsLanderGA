#ifndef INDIVIDUAL_H
# define INDIVIDUAL_H
# define GENES 200
# include <vector>
# include "Gene.h"
# include "Ship.h"
#define MAP_X 7000
#define MAP_Y 3000

class Mars;

class Individual
{
private:
	Gene				genes[GENES];
	Ship				ship;
	double				mark;

public:
	Individual();
	~Individual() = default;

	Individual& operator+=(const Individual& other);

	const double& getMark() const;

	Individual& setStartShip(const Ship& startShip);

	const Ship& getShip() const;

	Individual& computeLastPos(const Mars& mars, Point<double>* dispPop, const Ship& startShip);

	Individual& setMark(const double& mark);
	Individual& normMark(const double& sum);

	Individual& continuousBorn(const Individual& parent1, const Individual& parent2, const double& crossRate);

	Individual& born(const Individual& parent1, const Individual& parent2);

	bool isSolution(const Mars& mars, const unsigned int& vx, const unsigned int& vy, const unsigned int& minFuel);

private:
	Individual& computeMark(const Mars& mars);
};
#endif