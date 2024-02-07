#include "StoresMap.h"
StoresMap::StoresMap(const float a_gridWidth, const float a_gridHeight, const float a_gridSpacing, const HousesContainer& a_houses)
	:m_map{}
	, m_gridHeight{ a_gridHeight }
	, m_gridWidth{ a_gridWidth }
	, m_gridSpacing{ a_gridSpacing }
{
	//for (long i{ 0 }; i < m_gridWidth / m_gridSpacing; ++i)
	//{
	//	for (long j{ 0 }; j < m_gridHeight / a_gridSpacing; ++j)
	//	{
	//		//float x = RoundToGrid(i * m_gridSpacing, m_gridSpacing);
	//		//float y = RoundToGrid(j * m_gridSpacing, m_gridSpacing);
	//		//m_map.insert({ {x, y, StoreType::BIG}, Store{x,y,StoreType::BIG, a_houses} });
	//		//m_map.insert({ {x, y, StoreType::BIG}, Store{x,y,StoreType::SMALL, a_houses} });
	//	}
	//}
	size_t nCols = a_gridWidth / a_gridSpacing;
	size_t nRows = a_gridHeight / a_gridSpacing;
	m_map.resize(nRows);
	for (size_t yIdx{ 0 }; yIdx < nRows; ++yIdx)
	{
		Row row(nCols);
		for (size_t xIdx{ 0 }; xIdx < nCols; ++xIdx)
		{
			float x = xIdx * m_gridSpacing;
			float y = yIdx * m_gridSpacing;
			row[xIdx] = Cell{Store{x,y,StoreType::BIG, a_houses},Store{x,y,StoreType::SMALL, a_houses}};
		}
		m_map[yIdx] = row;
	}
}

const Store& StoresMap::at(const StoreKey& a_key) const 
{
	size_t xIdx = a_key.x / m_gridSpacing;
	size_t yIdx = a_key.y / m_gridSpacing;
	size_t cellIdx = (a_key.type == StoreType::BIG) ? 0 : 1;
	return m_map[yIdx][xIdx][cellIdx];
}

void StoresMap::insert(const std::pair<StoreKey, const Store&>& a_pair) 
{
	size_t xIdx = a_pair.first.x / m_gridSpacing;
	size_t yIdx = a_pair.first.y / m_gridSpacing;
	size_t cellIdx = (a_pair.first.type == StoreType::BIG) ? 0 : 1;
	m_map[xIdx][yIdx][cellIdx] = a_pair.second;
}
float StoresMap::GetSpacing() const
{
	return m_gridSpacing;
}

StoresMap::~StoresMap()
{
}


float RoundToGrid(const float& a_num, const float& a_gridSpacing)
{
	return std::round((long(a_num / a_gridSpacing) * float(a_gridSpacing)) * 1000)/1000.;
}