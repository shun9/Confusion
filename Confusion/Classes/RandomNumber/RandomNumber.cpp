//************************************************/
//* @file  :RandomNumber.cpp
//* @brief :���������N���X
//* @date  :2017/05/18
//* @author:S.Katou
//************************************************/
#include "RandomNumber.h"
#include <random>

//int�^�̗�������
int ShunLib::RandomNumber::operator()(int min, int max)
{
	//���������p
	std::random_device random;
	std::mt19937 mt(random());

	//�����̒l�𐧌�
	std::uniform_int_distribution<int> num(min, max);

	int result = num(mt);

	return result;
}

//float�^�̗�������
float ShunLib::RandomNumber::operator()(float min, float max)
{
	//���������p
	std::random_device random;
	std::mt19937 mt(random());

	//�����̒l�𐧌�
	std::uniform_real_distribution<float> num(min, max);

	float result = num(mt);

	return result;
}

//double�^�̗�������
double ShunLib::RandomNumber::operator()(double min, double max)
{
	//���������p
	std::random_device random;
	std::mt19937 mt(random());

	//�����̒l�𐧌�
	std::uniform_real_distribution<double> num(min, max);

	double result = num(mt);

	return result;
}
