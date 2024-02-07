#pragma once
struct Address
{
public:
	Address() = delete;
	Address(const float& a_xCoord, const float& a_yCoord) :xCoord{ a_xCoord }, yCoord{ a_yCoord } {}
	Address(const Address& a_other) :xCoord{ a_other.xCoord }, yCoord{ a_other.yCoord } {}
	~Address() {}

	float xCoord;
	float yCoord;
};

bool operator==(const Address& add1, const Address& add2);
bool operator!=(const Address& add1, const Address& add2);