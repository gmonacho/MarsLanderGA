#pragma once
#ifndef POPUATION_H
# define POPULATION_H
#define POP	  150
# include <vector>
# include "Individual.h"

class Population
{
private:
	Individual	group1[POP];
	Individual	group2[POP];

	Individual* currPop;
	Individual* nextPop;

	Individual* solution;

	Ship startShip;

public:
	Population(const Ship& startShip);
	~Population() = default;

	Population& nextGeneration(const Mars& mars, Point<double>** dispPop);

	bool		solutionFound() const;
	
	int			getAverageVx() const;

	int			getAverageVy() const;

	int			getAverageRotation() const;

	Individual* getSolution();


private:
	Population& checkSolution(const Mars& mars);

	struct {
		bool operator()(const Individual& a, const Individual& b) const
		{
			return a.getMark() < b.getMark();
		}
	} compareIndividual;

	Population& swapPops();

	Population& sortPop();

	double getMarkSum() const;

	Population& normPop(const double & sum);

	Population& computeCumulativeSum();

	const Individual& getCandidate() const;

	Population& generateNewPop();

	Population& rouletteWheel();

	Population& computeMarks(const Mars& mars, Point<double>** dispPop);
	
};

#endif