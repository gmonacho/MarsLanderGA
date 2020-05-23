#include "fun_array.h"
#include <algorithm>

double arrayAverage(const double* tab, const int& size)
{
	double sum{ 0 };
	for (int i = 0; i < size; i++)
		sum += tab[i];
	return (sum / static_cast<double>(size));
}

double* arraySort(double* tab, const int& size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (tab[i] < tab[j])
			{
				std::swap(tab[i], tab[j]);
				break;
			}
		}
	}
	return nullptr;
}
