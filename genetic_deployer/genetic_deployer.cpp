#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Parser.h"
//#include "Deployer.h"
#include "House.h"
#include "Store.h"
#include "Population.h"

int main()
{
	//std::cout << "Hello World!\n";
	//GenerateHousesFile("House_distribution.csv", 600, 800, 10, 2000);
	//Parser pars{ "House_distribution.csv" };
	//HousesContainer houses = pars.Parse();
	//Deployer deployer{ houses };
	//StoresContainer stores = deployer.Deploy();
	//std::cout << (CheckFullCoverage(stores, houses) ? "Fully Covered :P " : "Not fully covered!!!") << "\n";
	//GenerateStoresFile(stores, "store.csv");
	//std::cout << "Bye!";

	Parser pars{ "House_distribution.csv" };
	HousesContainer houses = pars.Parse();
	//Store s1{ Address{0,0},400,houses };
	//Store s2{ Address{800,800},400,houses };
	//Store s3{ Address{300,300},50,houses };
	StoreKey k1{ 0,0,StoreType::BIG };
	StoreKey k2{ 800,800,StoreType::BIG };
	StoreKey k3{ 300,300,StoreType::SMALL };
	StoresMap stores{ 600,800,20,houses };

	//stores.insert({ k1,Store{ Address{0,0},StoreType::BIG,houses } });
	//stores.insert({ k2,Store{ Address{800,800},StoreType::BIG,houses } });
	//stores.insert({ k3,Store{ Address{300,300},StoreType::BIG,houses } });
	//stores;
	Population pop{ 3000, 8, stores };
	pop.CalcPopulationFitness();

	std::cout << RoundToGrid(1243.123, 3) << "\n";
	std::cout << RoundToGrid(124.7123, 5) << "\n";
	std::cout << RoundToGrid(1243.723, 2.1) << "\n";
}

