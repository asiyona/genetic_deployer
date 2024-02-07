#include "Store.h"
#include "SupportFunctions.h"
#include "config.h"



Store::Store(const float& a_xCoord, const float& a_yCoord, const StoreType& a_type, const HousesContainer& a_houses)
	:m_address{ Address(a_xCoord,a_yCoord) },
	m_type{ a_type }
{
	m_proximateHouses = FindProximateHouses(*this, a_houses);
}

Store::Store(const Address& a_address, const StoreType& a_type, const HousesContainer& a_houses)
	:m_address{ a_address },
	m_type{ a_type}
{
	m_proximateHouses = FindProximateHouses(*this, a_houses);
}

const Address& Store::GetAddress() const
{
	return m_address;
}

const float Store::GetDeliveryRadius() const
{
	switch (m_type)
	{
	case BIG:
		return BIG_STORE_RADIUS;
	case SMALL:
		return SMALL_STORE_RADIUS;
	}
}

const float Store::GetRent() const
{
	switch (m_type)
	{
	case BIG:
		return BIG_STORE_RENT;
	case SMALL:
		return SMALL_STORE_RENT;
	}
}

const std::list<const House*> Store::GetProximateHouses() const
{
	return m_proximateHouses;
}


Store::ProxiHouses FindProximateHouses(const Store& a_store, const HousesContainer& a_houses)
{
	std::list<const House*> proximateHouseIds{};
	for (HousesContainer::const_iterator houseItr{ a_houses.begin() }; houseItr != a_houses.end(); ++houseItr)
	{
		if (IsProximate(a_store.GetAddress(), houseItr->second.GetAddress(), a_store.GetDeliveryRadius()))
		{
			proximateHouseIds.push_back(&(houseItr->second));//add house Id to list
		}
	}
	return proximateHouseIds;

}

