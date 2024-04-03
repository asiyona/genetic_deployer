#include "GeneticLogger.h"



GeneticLogger::GeneticLogger(const std::string a_fileName)
:m_fileStream{ a_fileName, std::ios::app }
//GeneticLogger::GeneticLogger(std::ofstream& a_fileStream)
//:m_fileStream{a_fileStream}
{
	//m_fileStream.open(a_fileName);
}

GeneticLogger::~GeneticLogger()
{
	m_fileStream.close();
}

void GeneticLogger::WriteLine(size_t n_stores, int generation, float generation_avg_fit, size_t gene_idx, float gene_fit, StoreKey storeKey)
{
	std::vector<std::string> cells;
	cells.push_back(std::to_string(n_stores));
	cells.push_back(std::to_string(generation));
	cells.push_back(std::to_string(generation_avg_fit));
	cells.push_back(std::to_string(gene_idx));
	cells.push_back(std::to_string(gene_fit));
	cells.push_back(std::to_string(storeKey.x));
	cells.push_back(std::to_string(storeKey.y));
	cells.push_back((storeKey.type == StoreType::BIG)?"BIG":"SMALL");
	WriteLineCsv(m_fileStream, cells);
}

void WriteLineCsv(std::ofstream& a_fstream,const std::vector<std::string>& a_strings)
{
	for (auto strItr{ a_strings.begin() };; )
	{
		a_fstream << *strItr;
		strItr++;
		if (strItr != a_strings.end())
		{
			a_fstream << ',';
		}
		else
		{
			a_fstream << '\n';
			return;
		}
	}
}