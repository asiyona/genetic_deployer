#pragma once
#include "Store.h"
#include "StoreKey.h"


class StoresMap
{
public:
	StoresMap() = delete;
	StoresMap(const float a_gridWidth, const float a_gridHeight, const float a_gridSpacing, const HousesContainer& a_houses);
	StoresMap(const StoresMap&) = delete;
	//StoresMap& operator=(const StoresMap&) = delete;
	const Store& at(const StoreKey& a_key) const;
	void insert(const std::pair<StoreKey, const Store&>& a_pair);
	float GetSpacing() const;
	float GetHeight() const {return m_gridHeight;}
	float GetWidth() const { return m_gridWidth;}
	
	~StoresMap();

private:

	//using Map = std::unordered_map<StoreKey, Store>;
	using Cell = std::vector<Store>;
	using Row = std::vector<Cell>;
	using Map= std::vector<Row>;

	Map m_map;
	float m_gridWidth;
	float m_gridHeight;
	float m_gridSpacing;
};


float RoundToGrid(const float& a_num, const float& a_gridSpacing, const float& a_gridMaxVal);
float RoundToGrid(const float& a_num, const float& a_gridSpacing);