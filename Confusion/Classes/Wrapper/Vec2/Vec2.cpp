//************************************************/
//* @file  :Vec2.cpp
//* @brief :2�����x�N�g���p�̃��b�v�N���X
//* @date  :2017/03/29
//* @author:K.Yamamoto
//************************************************/
#include "Vec2.h"
using namespace YamagenLib;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�t�H���g�R���X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Vec2::Vec2()
	:m_x(0)
	,m_y(0)
{

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�l�w��R���X�g���N�^
//�b����  :X,Y,Z(float,float,float)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Vec2::Vec2(float x, float y)
	:m_x(x)
	,m_y(y)
{

}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Vec2::~Vec2()
{

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�x�N�g����DirectX�̌`���ŕԂ�
//�b����  :�Ȃ��@�@(void)
//�b�߂�l:�x�N�g��(DirectX::SimpleMath::Vector3)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
DirectX::SimpleMath::Vector2 YamagenLib::Vec2::GetDirectVec2()
{
	DirectX::SimpleMath::Vector2 vec;
	vec.x = m_x;
	vec.y = m_y;
	return vec;
}

/*--[�ȉ��@���Z�q�̃I�[�o�[���[�h]--*/

Vec2& YamagenLib::Vec2::operator=(const Vec2& V)
{
	this->m_x = V.m_x;
	this->m_y = V.m_y;

	return *this;
}

Vec2& YamagenLib::Vec2::operator=(const DirectX::SimpleMath::Vector2& V)
{
	this->m_x = V.x;
	this->m_y = V.y;

	return *this;
}

Vec2& YamagenLib::Vec2::operator+(const Vec2& V)
{
	this->m_x += V.m_x;
	this->m_y += V.m_y;
	return *this;
}

Vec2& YamagenLib::Vec2::operator-(const Vec2& V)
{
	this->m_x -= V.m_x;
	this->m_y -= V.m_y;
	return *this;
}

Vec2& YamagenLib::Vec2::operator*(int num)
{
	this->m_x *= num;
	this->m_y *= num;

	return *this;
}
