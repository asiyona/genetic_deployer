#include "Population.h"



Population::Population(const size_t a_populationSize, const int a_storeNum, const StoresMap& a_map)
:m_genes(GenerateRandomPopulation(a_populationSize, a_storeNum, a_map))
,m_DNAsFitness(a_populationSize)
,m_map{a_map}
{
}

void Population::CalcPopulationFitness()
{
	for (size_t i = 0; i < m_genes.size(); i++)
	{
		m_DNAsFitness[i] = m_genes[i].GetFitness(m_map);
	}
}


std::vector<DNA> GenerateRandomPopulation(const size_t a_populationSize, const int a_storesNum, const StoresMap& a_map)
{
	std::vector<DNA> genes(a_populationSize);
	for (size_t i = 0; i < a_populationSize; i++)
	{
		genes[i] = GenerateRandomDNA(a_storesNum, a_map);
	}
	return genes;
}
