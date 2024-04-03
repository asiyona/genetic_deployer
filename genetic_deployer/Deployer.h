#pragma once
#include "House.h"
#include "StoresMap.h"
#include "Population.h"
#include "GeneticLogger.h"

class Deployer
{
public:
	Deployer() = delete;
	Deployer(const Deployer&) = delete;
	Deployer(const HousesContainer& a_houses, size_t a_storesNum, GeneticLogger& a_logger);
	~Deployer();

	std::list<Store> Deploy();

private:
	void LogGeneration(size_t a_generation, std::vector<float>& genFitness);
	const HousesContainer& m_houses;
	StoresMap m_map;
	Population m_population;
	GeneticLogger& m_logger;
};

