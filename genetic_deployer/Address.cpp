#include "Address.h"


bool operator==(const Address& add1, const Address& add2)
{
	return add1.xCoord == add2.xCoord && add1.yCoord == add2.yCoord;
}

bool operator!=(const Address& add1, const Address& add2)
{
	return !(add1 == add2);
}