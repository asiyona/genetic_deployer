#include "Parser.h"
//#include <iostream>
#include <fstream>
#include <array>
#include <sstream>

Parser::Parser(const std::string& a_fileName)
	:m_fileName{ a_fileName }
{}

//std::list<House> Parser::Parse()
//{
//	std::ifstream file{ m_fileName };
//	std::string line;
//	while (std::getline(file, line))
//	{
//
//	}
//}
//

Parser::~Parser()
{
}

HousesContainer Parser::Parse()
{
	HousesContainer houses{};
	std::ifstream file{ m_fileName };
	std::string line;
	std::getline(file, line);//skip first row
	while (std::getline(file, line))
	{
		House house = CreateHouse(line);
		houses.insert({ house.GetId(), house });
	}
	return houses;
}



House CreateHouse(const std::string& a_line)
{
	std::istringstream str{ a_line };
	std::string word;
	std::array<std::string, 4> words{};
	size_t i{ 0 };
	while (std::getline(str, word, ','))
	{
		words[i] = word;
		++i;
	}
	return House(words[0], std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));
}

