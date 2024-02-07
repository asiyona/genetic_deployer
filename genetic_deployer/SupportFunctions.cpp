#include "SupportFunctions.h"
#include <random>
#include <math.h>

bool IsProximate(const Address& a_first, const Address& a_second, const float& a_proximityDistnce)
{
	return Distance(a_first, a_second) <= a_proximityDistnce;
}

double Distance(const Address& a_first, const Address& a_second)
{
	return sqrt(pow(a_first.xCoord - a_second.xCoord, 2) + pow(a_first.yCoord - a_second.yCoord, 2));
}
