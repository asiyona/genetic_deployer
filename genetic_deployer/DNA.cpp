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
	return fitness > 0 ? fitness : 0;
}

void DNA::Mutate(const float& a_mutationRate, const float& a_typeMutationRate,const float& a_displacmentRate, const StoresMap& a_stores)
{
	//mutation rate sould be between 0 and 1
	std::random_device rd;  // Used to obtain a seed for the random number engine
	std::mt19937 randGenerator(rd()); // Mersenne Twister 19937 generator
	//std::default_random_engine randGenerator;
	std::normal_distribution<float> normDistribution{0, 1};
	std::uniform_real_distribution<float> uniDistribution{ 0,1 };
	float randNum = normDistribution(randGenerator);
	float gridSpacing = a_stores.GetSpacing();

	for (auto keyItr{ m_storesKeys.begin() }; keyItr != m_storesKeys.end(); ++keyItr)
	{
		//float uniDist = uniDistribution(randGenerator);
		if (uniDistribution(randGenerator) <= a_mutationRate)
		{
			float x_dispalace = RoundToGrid(normDistribution(randGenerator) * a_displacmentRate, gridSpacing, a_stores.GetWidth());
			float y_dispalace = RoundToGrid(normDistribution(randGenerator) * a_displacmentRate, gridSpacing, a_stores.GetHeight());
			float x = keyItr->x + x_dispalace;
			float y = keyItr->y + y_dispalace;
			keyItr->x = x > a_stores.GetWidth() ? a_stores.GetWidth(): x;
			keyItr->y = y > a_stores.GetHeight() ? a_stores.GetWidth() :y;
		}
		//if (abs(normDistribution(randGenerator)) > (1 - a_mutationRate * a_mutationRate))
		if (uniDistribution(randGenerator) <= a_typeMutationRate)
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

StoreKey GetRandomKeyFromSet(const std::unordered_set<StoreKey>& a_set)
{
	std::random_device rnd;
	auto setItr{ a_set.begin() };
	for (size_t i = 0; i < (rnd() % a_set.size()); i++)
	{
		++setItr;
	}
	return *setItr;
}

void FixDuplicates(DNA& a_child, const DNA& a_left, const DNA& a_right)
{
	std::random_device rnd;
	std::unordered_set<StoreKey> childSet;
	for (size_t i = 0; i < a_child.m_len; i++)
	{
		childSet.insert(a_child.GetKey(i));
	}
	if (childSet.size() == a_child.m_len)
	{
		return;
	}
	std::unordered_set<StoreKey> notSelectedSet;
	for (size_t i = 0; i < a_left.m_len; i++)
	{
		notSelectedSet.insert(a_left.GetKey(i));
		notSelectedSet.insert(a_right.GetKey(i));
	}
	for (auto setItr{ childSet .begin()}; setItr!= childSet.end(); ++setItr)
	{
		notSelectedSet.erase(*setItr);
	}
	while (childSet.size() != a_child.m_len)
	{ 
		for (size_t i = 0; i < a_child.m_len; i++)
		{
			for (size_t j = i + 1; j < a_child.m_len; j++)
			{
				if (a_child.GetKey(i) == a_child.GetKey(j))
				{
					StoreKey newKey = GetRandomKeyFromSet(notSelectedSet);
					notSelectedSet.erase(newKey);
					size_t idxChange{ (rnd() % 2) ? i : j };
					a_child.SetKey(idxChange, newKey);
					childSet.insert(newKey);
				}
			}
		}
	
	}
	return;
}

DNA Crossover(const DNA& a_left, const DNA& a_right)
{
	size_t len = a_left.m_len;
	DNA child = DNA(len);
	std::random_device rd;  // Used to obtain a seed for the random number engine
	for (size_t i = 0; i < len; i++)
	{
		child.SetKey(i, (rd() % 2) ? a_left.GetKey(i) : a_right.GetKey(i));
	}	
	FixDuplicates(child, a_left, a_right);
	return child;
}

DNA GenerateRandomDNA(const int a_len, const StoresMap& a_map)
{
	std::random_device rand{};
	StoresKeys keys(a_len);
	for (int i{ 0 }; i < a_len; ++i)
	{
		float x{ RoundToGrid((rand()) % int(a_map.GetWidth()), a_map.GetSpacing(), a_map.GetWidth()) };
		float y{ RoundToGrid((rand()) % int(a_map.GetHeight()), a_map.GetSpacing(), a_map.GetHeight()) };
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