//************************************************/
//* @file  :Gravity.h
//* @brief :�v���C���[��������d�͂̃N���X
//* @date  :2017/04/23
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Wrapper/Texture/Texture.h"
#include "../Wrapper/Matrix/Matrix.h"

class Gravity
{
private:
	static const float POWER;

private:
	ShunLib::Texture* m_texture;

	//���a
	float m_radius;

	//�ʒu
	ShunLib::Vec3 m_pos;

	//��]�p
	float m_angle;

public:
	//�R���X�g���N�^���f�X�g���N�^
	Gravity(const wchar_t* texture,
			const ShunLib::Vec3& pos = (0.0f, 0.0f, 0.0f));
	~Gravity();

	//�X�V
	void Update();

	//�`��
	void Draw(ShunLib::Matrix view, ShunLib::Matrix proj);

	//���a
	void Radius(float radius) { m_radius = radius; }
	float Radius() { return m_radius; }

	//�ʒu
	void Pos(ShunLib::Vec3 pos) { m_pos = pos; }
	void Pos(float x,float y,float z) 
	{
		m_pos.m_x = x; 
		m_pos.m_y = y;
		m_pos.m_z = z;
	}
	ShunLib::Vec3 Pos() { return m_pos; }

	//�Ώۂ������񂹂�
	void Attract(ShunLib::Vec3* objPos);
};
