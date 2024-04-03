#include "House.h"

House::House(const Id& a_id, const Address& a_address, const float& a_consumption)
	:m_id{ a_id },
	m_address{ a_address },
	m_consumption{ a_consumption }
{}


House::House(const Id& a_id, const float& a_xCoord, const float& a_yCoord, const float& a_consumption)
	:m_id{ a_id }
	, m_address{ Address(a_xCoord,a_yCoord) }
	, m_consumption{ a_consumption }
{}

const Address House::GetAddress() const
{
	return m_address;
}

const House::Id House::GetId() const
{
	return m_id;
}


const float House::GetConsumption() const
{
	return m_consumption;
}


std::pair<float, float> FindGridDimmenssions(const HousesContainer& a_houses)
{
	float xMax{ 0 };
	float yMax{ 0 };

	for (auto houseItr{ a_houses.begin() }; houseItr != a_houses.end(); ++houseItr)
	{
		xMax = std::max(houseItr->second.GetAddress().xCoord, xMax);
		yMax = std::max(houseItr->second.GetAddress().yCoord, yMax);
	}
	return { xMax,yMax };
}