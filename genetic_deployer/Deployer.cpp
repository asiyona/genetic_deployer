#include "Deployer.h"
#include "config.h"
#include <iostream>
#include <algorithm> 
#include <numeric>

Deployer::Deployer(const HousesContainer& a_houses, const size_t a_storesNum, GeneticLogger& a_logger)
:m_houses{a_houses}
,m_map{ FindGridDimmenssions(a_houses).first,FindGridDimmenssions(a_houses).second, GRID_SPACING, a_houses }
,m_population{ POPULATION_SIZE, int(a_storesNum), m_map }
,m_logger{a_logger}
{
}

Deployer::~Deployer()
{
}

std::list<Store> Deployer::Deploy()
{
	std::cout << "Num of stores: " << m_population.GetGeneSize() << " ";
	std::vector<double> averageFitness(GENERATIONS_NUM);
	std::vector< std::vector<float>> fitnessHist(GENERATIONS_NUM);
	for (size_t generation{ 0 }; generation < GENERATIONS_NUM; ++generation)
	{
		//Population nextGeneration{m_population.GetPopulationSize(), m_map};
		std::vector<float> populationFitness = m_population.CalcPopulationFitness();
		LogGeneration(generation, populationFitness);
		std::vector<DNA> nextGenerationGenes(m_population.GetPopulationSize());
		for (size_t i{ 0 }; i < m_population.GetPopulationSize(); ++i)
		{
			DNA child{ Crossover(m_population.NaturalSelectionDraw(),m_population.NaturalSelectionDraw()) };
			child.Mutate(LOCATION_MUTATION_RATIO,TYPE_MUTATION_RATIO, DISPLACMENT_RATE, m_map);
			nextGenerationGenes [i] = child;
		}
		m_population.SetGenes(nextGenerationGenes);
		std::cout << ".";
	}
	std::cout << "\n";
	return {};
}

template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T>& v) 
{
	std::vector<size_t> idx(v.size());
	iota(idx.begin(), idx.end(), 0);
	stable_sort(idx.begin(), idx.end(),
		[&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });

	return idx;
}

void Deployer::LogGeneration(size_t a_generation, std::vector<float>& a_genFitness)
{
	float genAvgFit = std::accumulate(a_genFitness.begin(), a_genFitness.end(), 0.0) / a_genFitness.size();
	std::vector<size_t> sortedIdx = sort_indexes(a_genFitness);
	int i{ 0 };
	const std::vector<DNA>& genes{m_population.GetGenes()};
	size_t storesNum{ m_population.GetGeneSize() };
	for (auto revIdxItr{ sortedIdx.rbegin() } ;  i<10;++revIdxItr,++i)
	{
		for (size_t i = 0; i < storesNum; i++)
		{
			m_logger.WriteLine(storesNum, a_generation, genAvgFit, *revIdxItr, a_genFitness[*revIdxItr], genes[*revIdxItr].GetKey(i));
		}
	}
}