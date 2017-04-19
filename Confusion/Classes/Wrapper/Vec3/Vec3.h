//************************************************/
//* @file  :Vec3.h
//* @brief :RณxNgpฬbvNX
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
		/*--[รIฯ]--*/
	public:
		static const Vec3 Zero;			// O  O  O
		static const Vec3 One;			// P  P  P
		static const Vec3 UnitX;		// P  O  O
		static const Vec3 UnitY;		// O  P  O
		static const Vec3 UnitZ;		// O  O  P
		static const Vec3 Up;			// O  P  O
		static const Vec3 Down;			// O -P  O
		static const Vec3 Right;		// P  O  O
		static const Vec3 Left;			//-P  O  O
		static const Vec3 Forward;		// O  O -P
		static const Vec3 Backward;		// O  O  P


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

		//xNg๐DirectXฬ`ฎลิท
		DirectX::SimpleMath::Vector3 GetDirectVec3();
	
		/*--[ZqฬI[o[[h]--*/
		Vec3& operator=(const Vec3& V);
		Vec3& operator=(const DirectX::SimpleMath::Vector3& V);
		Vec3& operator+(const Vec3& V);
		Vec3& operator-(const Vec3& V);
		Vec3& operator*(int num);

	};
}