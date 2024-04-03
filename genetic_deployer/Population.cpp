#include "Population.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <assert.h>

Population::Population(const Population& a_other)
	:m_DNAsFitness{a_other.m_DNAsFitness}
	,m_genes{a_other.m_genes}
	,m_map{a_other.m_map}
	,m_populationSize{a_other.m_populationSize}
{
}

Population& Population::operator=(const Population& a_other)
{
	m_DNAsFitness = a_other.m_DNAsFitness;
	m_genes = a_other.m_genes;
	m_populationSize = a_other.m_populationSize;
	m_map = a_other.m_map;
	return *this;
}

Population::Population(const size_t a_populationSize, const StoresMap& a_map)
:m_genes(a_populationSize)
,m_DNAsFitness(a_populationSize)
,m_map{&a_map}
,m_populationSize{a_populationSize}
{}

Population::Population(const size_t a_populationSize, const int a_storeNum, const StoresMap& a_map)
:m_genes(GenerateRandomGenes(a_populationSize, a_storeNum, a_map))
,m_DNAsFitness(a_populationSize)
,m_map{&a_map}
,m_populationSize{ a_populationSize }
{
}

std::vector<float> Population::CalcPopulationFitness()
{
	//double maxPopulationFitness{ 0 };
	for (size_t i = 0; i < m_genes.size(); i++)
	{
		m_DNAsFitness[i] = m_genes[i].GetFitness(*m_map);
		//if (m_DNAsFitness[i] > maxPopulationFitness)
		//{
		//	maxPopulationFitness = m_DNAsFitness[i];
		//}

	}
	return m_DNAsFitness;
}

const DNA& Population::NaturalSelectionDraw()
{
	size_t geneIdx = NaturalSelectionIdx(m_DNAsFitness);
	return m_genes[geneIdx];
}


void Population::GenerateRandomPopulation(const int a_storesNum)
{
	m_genes = GenerateRandomGenes(m_populationSize, a_storesNum, *m_map);
}


size_t Population::GetPopulationSize() const 
{ 
	return m_populationSize; 
}

void Population::SetGenes(const std::vector<DNA>& a_genes)
{
	assert(a_genes.size() == m_populationSize);
	m_genes = a_genes;
}
size_t Population::GetGeneSize()
{
	return m_genes[0].m_len;
}

const std::vector<DNA>& Population::GetGenes()
{
	return m_genes;
}


size_t NaturalSelectionIdx(const std::vector<float>& a_fitnessScores)
{
	double sum = std::accumulate(a_fitnessScores.begin(), a_fitnessScores.end(),0);
	std::uniform_real_distribution<double> unif(0, sum);
	std::random_device rd;  // Used to obtain a seed for the random number engine
	std::mt19937 rndEng(rd()); // Mersenne Twister 19937 generator
	//std::default_random_engine rndEng;
	double randomNum = unif(rndEng);
	double accumlator{ 0 };
	for (size_t i = 0; i < a_fitnessScores.size(); ++i)
	{
		accumlator += a_fitnessScores[i];
		if (accumlator > randomNum)
		{
			return i;
		}
	}
	assert(!("should never get here"));
}

std::vector<DNA> GenerateRandomGenes(const size_t a_populationSize, const int a_storesNum, const StoresMap& a_map)
{
	std::vector<DNA> genes(a_populationSize);
	for (size_t i = 0; i < a_populationSize; i++)
	{
		genes[i] = GenerateRandomDNA(a_storesNum, a_map);
	}
	return genes;
}
