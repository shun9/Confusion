//************************************************/
//* @file  :Vec3.h
//* @brief :‚RŸŒ³ƒxƒNƒgƒ‹—p‚Ìƒ‰ƒbƒvƒNƒ‰ƒX
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
		/*--[Ã“I•Ï”]--*/
	public:
		static const Vec3 Zero;			// ‚O  ‚O  ‚O
		static const Vec3 One;			// ‚P  ‚P  ‚P
		static const Vec3 UnitX;		// ‚P  ‚O  ‚O
		static const Vec3 UnitY;		// ‚O  ‚P  ‚O
		static const Vec3 UnitZ;		// ‚O  ‚O  ‚P
		static const Vec3 Up;			// ‚O  ‚P  ‚O
		static const Vec3 Down;			// ‚O -‚P  ‚O
		static const Vec3 Right;		// ‚P  ‚O  ‚O
		static const Vec3 Left;			//-‚P  ‚O  ‚O
		static const Vec3 Forward;		// ‚O  ‚O -‚P
		static const Vec3 Backward;		// ‚O  ‚O  ‚P


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

		//ƒxƒNƒgƒ‹‚ğDirectX‚ÌŒ`®‚Å•Ô‚·
		DirectX::SimpleMath::Vector3 GetDirectVec3();
	
		/*--[‰‰Zq‚ÌƒI[ƒo[ƒ[ƒh]--*/
		Vec3& operator=(const Vec3& V);
		Vec3& operator=(const DirectX::SimpleMath::Vector3& V);
		Vec3& operator+(const Vec3& V);
		Vec3& operator-(const Vec3& V);

		template<class T>Vec3& operator*(T num);
		template<class T>Vec3& operator/(T num);

	};

	template<class T>
	inline Vec3& Vec3::operator*(T num)
	{
		this->m_x *= static_cast<float>(num);
		this->m_y *= static_cast<float>(num);
		this->m_z *= static_cast<float>(num);
		return *this;
	}

	template<class T>
	inline Vec3& Vec3::operator/(T num)
	{
		this->m_x /= static_cast<float>(num);
		this->m_y /= static_cast<float>(num);
		this->m_z /= static_cast<float>(num);
		return *this;
	}

}

