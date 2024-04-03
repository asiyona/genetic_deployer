#pragma once
#include "DNA.h"
#include <utility>
class Population
{
public:
	Population() = delete;
	Population(const Population& a_other);
	Population& operator=(const Population& a_other);

	Population(const size_t a_populationSize, const StoresMap& a_map);
	Population(const size_t a_populationSize, const int a_storeNum, const StoresMap& a_map);
	std::vector<float> CalcPopulationFitness();
	const DNA& NaturalSelectionDraw();
	void GenerateRandomPopulation(const int a_storesNum);
	size_t GetPopulationSize() const;
	void SetGenes(const std::vector<DNA>& a_genes);
	size_t GetGeneSize();
	const std::vector<DNA>& GetGenes();

private:
	std::vector<DNA> m_genes;
	std::vector<float> m_DNAsFitness;
	const StoresMap* m_map;
	size_t m_populationSize;
};

std::vector<DNA> GenerateRandomGenes(const size_t a_populationSize, const int a_storesNum, const StoresMap& a_map);
size_t NaturalSelectionIdx(const std::vector<float>& a_fitnessScores);