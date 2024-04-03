#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "config.h"
#include "Parser.h"
//#include "Deployer.h"
#include "House.h"
#include "Store.h"
#include "Population.h"
#include "Deployer.h"

const std::vector<std::string> COL_NAMES{
	"n_stores",
	"generation",
	"generation_avg_fit",
	"gene_idx",
	"gene_fit",
	"x_store",
	"y_store",
	"store_type"
};

int main()
{
	std::ofstream file;
	Parser pars{ "House_distribution.csv" };
	HousesContainer houses = pars.Parse(); std::cout << "Houses created" << "\n";

	{
		std::ofstream resetFile{ "evolotionLog.csv" };
		WriteLineCsv(resetFile, COL_NAMES); 
	}
	for (size_t storeNum = 32; storeNum < 33; storeNum+=3)
	{
		GeneticLogger logger{ "evolotionLog.csv" };
		Deployer deployer{ houses, storeNum ,logger };
		std::list<Store> best_stores = deployer.Deploy();
		
	}

	//Population pop{ 3000, 8, stores };
	//pop.CalcPopulationFitness();
	//for (size_t i = 0; i < 3000; i++)
	//{
	//	DNA gene = pop.NaturalSelectionDraw();
	//	//std::cout << "gene #" << i << ":\n";
	//	//std::cout << "pre mutate: ";
	//	//gene.Print();
	//	gene.Mutate(0.3 ,30, stores);
	//	//std::cout << "post mutate: ";
	//	//gene.Print();
	//	//std::cout << std::endl;
	//}
}

