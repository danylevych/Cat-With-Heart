#pragma once

#include <random>
#include "Range.h"


template<typename NumType = int, typename RealType = float>
class Random
{
private:
	std::mt19937 engine;
	std::uniform_int_distribution<NumType> numDis;
	std::uniform_real_distribution<RealType> realDis;

public:
	Random();

public:
	NumType GetRandomNumber(Range<NumType> range);

	NumType GetRandomNumber(NumType begin, NumType end);

	RealType GetRandomRealNumber(Range<RealType> range);

	RealType GetRandomRealNumber(RealType begin, RealType end);
	
};


template<typename NumType, typename RealType>
inline Random<NumType, RealType>::Random()
	: engine(std::random_device()())
	, numDis()
	, realDis()
{	}

template<typename NumType, typename RealType>
inline NumType Random<NumType, RealType>::GetRandomNumber(Range<NumType> range)
{
	return GetRandomNumber(range.min, range.max);
}

template<typename NumType, typename RealType>
inline NumType Random<NumType, RealType>::GetRandomNumber(NumType begin, NumType end)
{
	return numDis(engine, std::uniform_int_distribution<NumType>::param_type(begin, end));
}

template<typename NumType, typename RealType>
inline RealType Random<NumType, RealType>::GetRandomRealNumber(Range<RealType> range)
{
	return GetRandomRealNumber(range.min, range.max);
}

template<typename NumType, typename RealType>
inline RealType Random<NumType, RealType>::GetRandomRealNumber(RealType begin, RealType end)
{
	return realDis(engine, std::uniform_real_distribution<RealType>::param_type(begin, end));
}
