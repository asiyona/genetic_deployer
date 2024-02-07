#pragma once
#include "Store.h"

struct StoreKey
{
	float x;
	float y;
	StoreType type;
};

bool operator==(const StoreKey&, const StoreKey&);

template<>
struct std::hash<StoreKey>
{
	inline size_t operator()(const StoreKey& K) const
	{
		return size_t((size_t(std::hash<float>()(K.x) / 2) + size_t(std::hash<float>()(K.y) / 2)) / 100);
	}
};
