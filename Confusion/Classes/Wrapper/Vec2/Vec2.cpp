//************************************************/
//* @file  :Vec2.cpp
//* @brief :2次元ベクトル用のラップクラス
//* @date  :2017/03/29
//* @author:K.Yamamoto
//************************************************/
#include "Vec2.h"
using namespace YamagenLib;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デフォルトコンストラクタ
//＋ーーーーーーーーーーーーーー＋
Vec2::Vec2()
	:m_x(0)
	,m_y(0)
{

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :値指定コンストラクタ
//｜引数  :X,Y,Z(float,float,float)
//＋ーーーーーーーーーーーーーー＋
Vec2::Vec2(float x, float y)
	:m_x(x)
	,m_y(y)
{

}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Vec2::~Vec2()
{

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :ベクトルをDirectXの形式で返す
//｜引数  :なし　　(void)
//｜戻り値:ベクトル(DirectX::SimpleMath::Vector3)	
//＋ーーーーーーーーーーーーーー＋
DirectX::SimpleMath::Vector2 YamagenLib::Vec2::GetDirectVec2()
{
	DirectX::SimpleMath::Vector2 vec;
	vec.x = m_x;
	vec.y = m_y;
	return vec;
}

/*--[以下　演算子のオーバーロード]--*/

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
