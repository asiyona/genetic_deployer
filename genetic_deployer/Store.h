#pragma once
#include <list>
#include <unordered_map>
#include "Address.h"
#include "House.h"

enum StoreType
{
	BIG,
	SMALL
};


class Store
{
public:
	using ProxiHouses = std::list<const House*>;
	Store() = delete;
	Store(const float& a_xCoord, const float& a_yCoord, const StoreType& a_type, const HousesContainer& a_houses);
	Store(const Address& a_address, const StoreType& a_type, const HousesContainer& a_houses);
	const Address& GetAddress() const;
	const float GetDeliveryRadius() const;
	const ProxiHouses GetProximateHouses() const;
	const float GetRent() const;

	~Store() {}

private:
	Address m_address;
	StoreType m_type;
	//float m_deliveryRadius;
	ProxiHouses m_proximateHouses;
	//float m_rent;
};

//using StoresMap = std::unordered_map<StoreKey, Store>;

Store::ProxiHouses FindProximateHouses(const Store& a_stores, const HousesContainer& a_houses);
