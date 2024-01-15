#pragma once

#include <random>

//////////////////////////////////////////
// \brief
//			Store the range.
//////////////////////////////////////////
template<typename Type>
struct Range
{
	Type min;
	Type max;
};

using RangeI = Range<int>;
using RangeF = Range<float>;