//************************************************/
//* @file  :RandomNumber.cpp
//* @brief :乱数生成クラス
//* @date  :2017/05/18
//* @author:S.Katou
//************************************************/
#include "RandomNumber.h"
#include <random>

//int型の乱数生成
int ShunLib::RandomNumber::operator()(int min, int max)
{
	//乱数生成用
	std::random_device random;
	std::mt19937 mt(random());

	//乱数の値を制限
	std::uniform_int_distribution<int> num(min, max);

	int result = num(mt);

	return result;
}

//float型の乱数生成
float ShunLib::RandomNumber::operator()(float min, float max)
{
	//乱数生成用
	std::random_device random;
	std::mt19937 mt(random());

	//乱数の値を制限
	std::uniform_real_distribution<float> num(min, max);

	float result = num(mt);

	return result;
}

//double型の乱数生成
double ShunLib::RandomNumber::operator()(double min, double max)
{
	//乱数生成用
	std::random_device random;
	std::mt19937 mt(random());

	//乱数の値を制限
	std::uniform_real_distribution<double> num(min, max);

	double result = num(mt);

	return result;
}
