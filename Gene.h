#ifndef GENE_H
# define GENE_H

class Gene
{
private:
	int rotation;
	int	power;

public:
	Gene();

	Gene(int rotation, int power);

	~Gene() = default;

	const int& getRotation() const;
	const int& getPower() const;

	Gene& evolve(const Gene& p1, const Gene& p2, const double& crossRate);
	Gene& mutate();
	Gene& hardMutate();
	Gene& setRotation(const int& rotation);

};

#endif