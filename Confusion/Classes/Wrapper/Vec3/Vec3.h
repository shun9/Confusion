//************************************************/
//* @file  :Vec3.h
//* @brief :�R�����x�N�g���p�̃��b�v�N���X
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
		/*--[�ÓI�ϐ�]--*/
	public:
		static const Vec3 Zero;			// �O  �O  �O
		static const Vec3 One;			// �P  �P  �P
		static const Vec3 UnitX;		// �P  �O  �O
		static const Vec3 UnitY;		// �O  �P  �O
		static const Vec3 UnitZ;		// �O  �O  �P
		static const Vec3 Up;			// �O  �P  �O
		static const Vec3 Down;			// �O -�P  �O
		static const Vec3 Right;		// �P  �O  �O
		static const Vec3 Left;			//-�P  �O  �O
		static const Vec3 Forward;		// �O  �O -�P
		static const Vec3 Backward;		// �O  �O  �P


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

		//�x�N�g����DirectX�̌`���ŕԂ�
		DirectX::SimpleMath::Vector3 GetDirectVec3();
	
		/*--[���Z�q�̃I�[�o�[���[�h]--*/
		//bool  operator==(const Vec3& V);
		Vec3& operator=(const Vec3& V);
		Vec3& operator=(const DirectX::SimpleMath::Vector3& V);
		Vec3 operator+(const Vec3& V);
		Vec3 operator-(const Vec3& V);
		Vec3 operator*(float num);
		Vec3 operator/(float num);

	};


	////���Z�q�̃I�[�o�[���[�h
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
//��r���Z�q�̃I�[�o�[���[�h
//�����o�ŏ�肭�����Ȃ������̂ŃO���[�o��
bool  operator==(const ShunLib::Vec3& V, const ShunLib::Vec3& V2);

