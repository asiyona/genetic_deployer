#pragma once
#include <string>
#include <list>
#include "House.h"

// TODO: should create free function instead?
class Parser
{
public:
	Parser() = delete;
	Parser(const Parser&) = delete;
	Parser(const std::string& a_fileName);
	~Parser();
	HousesContainer Parse();

private:
	const std::string m_fileName;
};

House CreateHouse(const std::string& a_line);

