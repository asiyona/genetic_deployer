#pragma once
#include "DNA.h"

class Population
{
public:
	Population() = delete;
	Population(const size_t a_populationSize, const int a_storeNum, const StoresMap& a_map);
	void CalcPopulationFitness();
private:
	std::vector<DNA> m_genes;
	std::vector<float> m_DNAsFitness;
	const StoresMap& m_map;
};

std::vector<DNA> GenerateRandomPopulation(const size_t a_populationSize, const int a_storesNum, const StoresMap& a_map);