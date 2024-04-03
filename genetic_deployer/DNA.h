#pragma once
#include <vector>
#include "Store.h"
#include <unordered_map>
#include "House.h"
#include "StoresMap.h"


using StoresKeys = std::vector<StoreKey>;

class DNA
{
public:
	DNA() = default;
	DNA(const StoresKeys& a_keys);
	DNA(int a_len);
	DNA(const StoresKeys& a_keys, const int a_len);
	float GetFitness(const StoresMap& a_stores) const;
	void Mutate(const float& a_mutationRate, const float& a_typeMutationRate, const float& a_displacmentRate, const StoresMap& a_stores);
	StoreKey GetKey(const size_t a_idx) const;
	void SetKey(const size_t a_idx, const StoreKey& a_key);
	void Print();

	int m_len;
private:
	StoresKeys m_storesKeys;


};



DNA GenerateRandomDNA(const int a_len, const StoresMap& a_map);
DNA Crossover(const DNA& a_left, const DNA& a_right);