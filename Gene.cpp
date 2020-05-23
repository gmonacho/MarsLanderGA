#include <cstdlib>
#include <algorithm>
#include "Gene.h"

Gene::Gene()
{
	this->mutate();
}

Gene::Gene(int rotation, int power)
{
	this->rotation = std::clamp(rotation, -15, 15);
	this->power = std::clamp(power, -1, 1);
}

const int& Gene::getRotation() const
{
	return (this->rotation);
}

const int& Gene::getPower() const
{
	return (this->power);
}

Gene& Gene::evolve(const Gene& p1, const Gene& p2, const double& crossRate)
{
	this->rotation = static_cast<int>(crossRate * p1.rotation + (1 - crossRate) * p2.rotation);
	this->power = static_cast<int>(crossRate * p1.power + (1 - crossRate) * p2.power);
	return (*this);
}

Gene& Gene::mutate()
{
	this->rotation = (std::rand() % 31) - 15;
	this->power = (std::rand() % 3) - 1;
	return (*this);
}

Gene& Gene::hardMutate()
{
	this->rotation = (std::rand() % 2 == 0) ? -15 : 15;
	this->power = (std::rand() % 3) - 1;
	return (*this);
}

Gene& Gene::setRotation(const int& rotation)
{
	this->rotation = rotation;
	return (*this);
}
