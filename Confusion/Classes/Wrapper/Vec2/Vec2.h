//************************************************/
//* @file  :Vec2.h
//* @brief :2�����x�N�g���p�̃��b�v�N���X
//* @date  :2017/03/29
//* @author:K.Yamamoto
//************************************************/

// ���d�C���N���[�h�h�~
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11.h>
#include <SimpleMath.h>

// ���O��Ԏg�p
namespace YamagenLib
{
	// Vec2�N���X
	class Vec2
	{
	public:
		float m_x;
		float m_y;

	public:
		Vec2();
		Vec2(float x, float y);
		~Vec2();

		// �x�N�g����DirectX�̌`���ŕԂ�
		DirectX::SimpleMath::Vector2 GetDirectVec2();
	
		/*--[���Z�q�̃I�[�o�[���[�h]--*/
		Vec2& operator=(const Vec2& V);
		Vec2& operator=(const DirectX::SimpleMath::Vector2& V);
		Vec2& operator+(const Vec2& V);
		Vec2& operator-(const Vec2& V);
		Vec2& operator*(int num);

	};
}