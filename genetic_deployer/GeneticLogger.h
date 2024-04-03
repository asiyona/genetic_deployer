#pragma once
#include <fstream>
#include <vector>
#include "StoreKey.h"


class GeneticLogger
{
public:
	GeneticLogger() = delete;
	GeneticLogger(const std::string a_fileName);
	//GeneticLogger(std::ofstream& a_fileStream);
	~GeneticLogger();

	void WriteLine(size_t n_stores, int generation, float generation_avg_fit, size_t gene_idx, float gene_fit, StoreKey storeKey);
//private:
	std::ofstream m_fileStream;
};

void WriteLineCsv(std::ofstream& a_fstream, const std::vector<std::string>& a_strings);



