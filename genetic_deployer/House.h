#pragma once
#include "Address.h"
#include <string>
#include <unordered_map>

class House
{
public:
	using Id = std::string;
	House() = delete;
	House(const Id& a_id, const Address& a_address, const float& a_consumption);
	House(const Id& a_id, const float& a_xCoord, const float& a_yCoord, const float& a_consumption);
	~House() {}
	const Address GetAddress() const;
	const Id GetId() const;
	const float GetConsumption() const;

private:
	Id m_id;
	Address m_address;
	float m_consumption;
};

//TODO: where should this line be?
using HousesContainer = std::unordered_map<House::Id, House>;