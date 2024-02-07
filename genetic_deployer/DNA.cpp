#include "DNA.h"
#include <unordered_set>
#include <random>
#include <iostream>

DNA::DNA(const StoresKeys& a_keys)
:m_storesKeys{ a_keys }
{
	m_len = m_storesKeys.size();
}

DNA::DNA(int a_len)
:m_storesKeys( a_len )
,m_len{a_len}
{
}

DNA::DNA(const StoresKeys& a_keys, const int a_len)
:m_storesKeys{ a_keys }
,m_len{ a_len }
{
}

float DNA::GetFitness(const StoresMap&a_stores) const
{
	float fitness{ 0 };
	std::unordered_set<House::Id> visitedHouses{};
	for (auto keyItr{ m_storesKeys.begin() }; keyItr != m_storesKeys.end(); ++keyItr)
	{
		const Store::ProxiHouses proxiHouses = a_stores.at(*keyItr).GetProximateHouses();
		for (auto houseItr{ proxiHouses.begin() }; houseItr!= proxiHouses.end();++houseItr)
		{
			if (!visitedHouses.count((*houseItr)->GetId()))//if house ID not in set add
			{
				fitness += (*houseItr)->GetConsumption();
				visitedHouses.insert((*houseItr)->GetId());
			}
		}
		fitness -= a_stores.at(*keyItr).GetRent();
	}
	return fitness;
}

void DNA::Mutate(const float& a_mutationRate,const float& a_displacmentRate, const StoresMap& a_stores)
{
	//mutation rate sould be between 0 and 1
	std::default_random_engine randGenerator;
	std::normal_distribution<float> distribution{0, 1};
	float randNum = distribution(randGenerator);
	float gridSpacing = a_stores.GetSpacing();

	for (auto keyItr{ m_storesKeys.begin() }; keyItr != m_storesKeys.end(); ++keyItr)
	{
		if (abs(distribution(randGenerator)) > (1 - a_mutationRate))
		{
			float x_dispalace = RoundToGrid(distribution(randGenerator) * a_displacmentRate, gridSpacing);
			float y_dispalace = RoundToGrid(distribution(randGenerator) * a_displacmentRate, gridSpacing);
			keyItr->x += x_dispalace; 
			keyItr->y += y_dispalace;
		}
		if (abs(distribution(randGenerator)) > (1 - a_mutationRate * a_mutationRate))
		{//toggle store type
			keyItr->type = (keyItr->type == StoreType::BIG) ? StoreType::SMALL : StoreType::BIG;
		}
	}
}

void DNA::SetKey(const size_t a_idx, const StoreKey& a_key)
{
	m_storesKeys[a_idx] = a_key;
}

StoreKey DNA::GetKey(const size_t a_idx) const
{
	return m_storesKeys[a_idx];
}

DNA Crossover(const DNA& a_left, const DNA& a_right)
{
	DNA child{ a_left.m_len };
	return child;
}

DNA GenerateRandomDNA(const int a_len, const StoresMap& a_map)
{
	std::random_device rand{};
	StoresKeys keys(a_len);
	for (int i{ 0 }; i < a_len; ++i)
	{
		float x{ RoundToGrid((rand()) % int(a_map.GetWidth()), a_map.GetSpacing()) };
		float y{ RoundToGrid((rand()) % int(a_map.GetHeight()), a_map.GetSpacing()) };
		StoreType type = (rand()) % 2 ? StoreType::SMALL : StoreType::BIG;
		keys[i] = StoreKey{ x,y,type };
	}
	return DNA{ keys, a_len };
}





void DNA::Print()
{
	std::cout << "[";

	for (size_t i = 0; i < m_len; i++)
	{
		std::cout << "{" << m_storesKeys[i].x << ", " << m_storesKeys[i].y << ", " << (m_storesKeys[i].type == StoreType::BIG ? "L" : "S") << "}";
	}
	std::cout << "]\n";
}