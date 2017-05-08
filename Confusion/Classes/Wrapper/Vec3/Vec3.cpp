//************************************************/
//* @file  :Vec3.cpp
//* @brief :３次元ベクトル用のラップクラス
//* @date  :2017/05/06
//* @author:S.Katou
//************************************************/
#include "Vec3.h"
using namespace ShunLib;

const Vec3 Vec3::Zero     = Vec3( 0 );
const Vec3 Vec3::One      = Vec3( 1 );
const Vec3 Vec3::UnitX    = Vec3( 1,  0,  0);
const Vec3 Vec3::UnitY    = Vec3( 0,  1,  0);
const Vec3 Vec3::UnitZ    = Vec3( 0,  0,  1);
const Vec3 Vec3::Up       = Vec3( 0,  1,  0);
const Vec3 Vec3::Down     = Vec3( 0, -1,  0);
const Vec3 Vec3::Right    = Vec3( 1,  0,  0);
const Vec3 Vec3::Left     = Vec3(-1,  0,  0);
const Vec3 Vec3::Forward  = Vec3( 0,  0, -1);
const Vec3 Vec3::Backward = Vec3( 0,  0,  1);

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デフォルトコンストラクタ
//＋ーーーーーーーーーーーーーー＋
Vec3::Vec3()
	:m_x(0)
	,m_y(0)
	,m_z(0)
{

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :値指定コンストラクタ
//｜引数  :X,Y,Z(float,float,float)
//＋ーーーーーーーーーーーーーー＋
Vec3::Vec3(float x, float y, float z)
	: m_x(x)
	, m_y(y)
	, m_z(z)
{

}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :値指定コンストラクタ
//｜引数  :X,Y,Z(float,float,float)
//＋ーーーーーーーーーーーーーー＋
Vec3::Vec3(float num)
	: m_x(num)
	, m_y(num)
	, m_z(num)
{

}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コピーコンストラクタ
//＋ーーーーーーーーーーーーーー＋
Vec3::Vec3(const Vec3& vec)
	: m_x(vec.m_x)
	, m_y(vec.m_y)
	, m_z(vec.m_z)
{
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Vec3::~Vec3()
{

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :ベクトルを正規化する
//｜引数  :なし　　(void)
//｜戻り値:なし　　(void)	
//＋ーーーーーーーーーーーーーー＋
void Vec3::Normalize()
{
	float length = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);

	m_x /= length;
	m_y /= length;
	m_z /= length;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :ベクトルをDirectXの形式で返す
//｜引数  :なし　　(void)
//｜戻り値:ベクトル(DirectX::SimpleMath::Vector3)	
//＋ーーーーーーーーーーーーーー＋
DirectX::SimpleMath::Vector3 Vec3::GetDirectVec3()
{
	DirectX::SimpleMath::Vector3 vec;
	vec.x = m_x;
	vec.y = m_y;
	vec.z = m_z;
	return vec;
}

/*--[以下　演算子のオーバーロード]--*/
bool  operator==(const ShunLib::Vec3& V, const ShunLib::Vec3& V2)
{
	return (V.m_x == V2.m_x
		  &&V.m_y == V2.m_y
		  &&V.m_z == V2.m_z);
}

//bool Vec3::operator==(const Vec3& V)
//{
//	if (this->m_x == V.m_x
//	  &&this->m_y == V.m_y
//	  &&this->m_z == V.m_z)
//	{
//		return true;
//	}
//
//	return false;
//}

Vec3& Vec3::operator=(const Vec3& V)
{
	this->m_x = V.m_x;
	this->m_y = V.m_y;
	this->m_z = V.m_z;

	return *this;
}

Vec3& Vec3::operator=(const DirectX::SimpleMath::Vector3& V)
{
	this->m_x = V.x;
	this->m_y = V.y;
	this->m_z = V.z;

	return *this;
}

Vec3 Vec3::operator+(const Vec3& V)
{
	Vec3 vec;
	vec.m_x = this->m_x + V.m_x;
	vec.m_y = this->m_y + V.m_y;
	vec.m_z = this->m_z + V.m_z;
	return vec;
}

Vec3 Vec3::operator-(const Vec3& V)
{
	Vec3 vec;
	vec.m_x = this->m_x - V.m_x;
	vec.m_y = this->m_y - V.m_y;
	vec.m_z = this->m_z - V.m_z;
	return vec;
}

ShunLib::Vec3 ShunLib::Vec3::operator*(float num)
{
	Vec3 vec;
	vec.m_x = this->m_x * static_cast<float>(num);
	vec.m_y = this->m_y * static_cast<float>(num);
	vec.m_z = this->m_z * static_cast<float>(num);
	return vec;
}

ShunLib::Vec3 ShunLib::Vec3::operator/(float num)
{
	Vec3 vec;
	vec.m_x = this->m_x / static_cast<float>(num);
	vec.m_y = this->m_y / static_cast<float>(num);
	vec.m_z = this->m_z / static_cast<float>(num);
	return vec;
}

//ShunLib::Vec3 & operator*(ShunLib::Vec3& V,float num)
//{
//	V.m_x *= static_cast<float>(num);
//	V.m_y *= static_cast<float>(num);
//	V.m_z *= static_cast<float>(num);
//	return V;
//}
//
//ShunLib::Vec3 & operator/(ShunLib::Vec3& V,float num)
//{
//	V.m_x /= static_cast<float>(num);
//	V.m_y /= static_cast<float>(num);
//	V.m_z /= static_cast<float>(num);
//	return V;
//}
//
