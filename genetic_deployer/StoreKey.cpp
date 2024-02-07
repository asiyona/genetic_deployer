#include "StoreKey.h"
bool operator==(const StoreKey& a, const StoreKey& b)
{
	return (a.type == b.type && a.x == b.x && a.y == b.y);
}
