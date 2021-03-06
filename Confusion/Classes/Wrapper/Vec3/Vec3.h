//************************************************/
//* @file  :Vec3.h
//* @brief :３次元ベクトル用のラップクラス
//* @date  :2017/02/22
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

namespace ShunLib
{
	class Vec3
	{
		/*--[静的変数]--*/
	public:
		static const Vec3 Zero;			// ０  ０  ０
		static const Vec3 One;			// １  １  １
		static const Vec3 UnitX;		// １  ０  ０
		static const Vec3 UnitY;		// ０  １  ０
		static const Vec3 UnitZ;		// ０  ０  １
		static const Vec3 Up;			// ０  １  ０
		static const Vec3 Down;			// ０ -１  ０
		static const Vec3 Right;		// １  ０  ０
		static const Vec3 Left;			//-１  ０  ０
		static const Vec3 Forward;		// ０  ０ -１
		static const Vec3 Backward;		// ０  ０  １


	public:
		float m_x;
		float m_y;
		float m_z;

	public:
		Vec3();
		Vec3(float x, float y, float z);
		Vec3(float num);
		Vec3(const Vec3& vec);
		~Vec3();

		void Normalize();

		//ベクトルをDirectXの形式で返す
		DirectX::SimpleMath::Vector3 GetDirectVec3();
	
		/*--[演算子のオーバーロード]--*/
		//bool  operator==(const Vec3& V);
		Vec3& operator=(const Vec3& V);
		Vec3& operator=(const DirectX::SimpleMath::Vector3& V);
		Vec3 operator+(const Vec3& V);
		Vec3 operator-(const Vec3& V);
		Vec3 operator*(float num);
		Vec3 operator/(float num);

	};


	////演算子のオーバーロード
	//template<class T>
	//inline Vec3& Vec3::operator*(T num)
	//{
	//	this->m_x *= static_cast<float>(num);
	//	this->m_y *= static_cast<float>(num);
	//	this->m_z *= static_cast<float>(num);
	//	return *this;
	//}

	//template<class T>
	//inline Vec3& Vec3::operator/(T num)
	//{
	//	this->m_x /= static_cast<float>(num);
	//	this->m_y /= static_cast<float>(num);
	//	this->m_z /= static_cast<float>(num);
	//	return *this;
	//}

}
//比較演算子のオーバーロード
//メンバで上手くいかなかったのでグローバル
bool  operator==(const ShunLib::Vec3& V, const ShunLib::Vec3& V2);

