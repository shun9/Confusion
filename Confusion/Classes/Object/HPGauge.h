//************************************************/
//* @file  :HPGauge.h
//* @brief :�q�b�g�|�C���g�N���X
//* @date  :2017/05/11
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Wrapper/Texture/Texture.h"

class HPGauge
{
private:
	//�摜
	ShunLib::Texture* m_green;
	ShunLib::Texture* m_red;

	//�ő�g�o�ƌ��݂̂g�o
	const int MAX_HP;
	int m_hp;

	//�\���p�p�����[�^
	ShunLib::Vec3* m_pos;
	ShunLib::Vec3* m_scale;
	ShunLib::Vec3* m_rotate;

public:
	HPGauge(int max, ShunLib::Vec3 pos, ShunLib::Vec3 scale, ShunLib::Vec3 rotate);
	~HPGauge();
	void Draw(const ShunLib::Matrix& view, const ShunLib::Matrix& proj);

	//�q�b�g�|�C���g
	void HP(int hp) { m_hp = hp; }
	int HP() { return m_hp; }

	//�ʒu
	void Pos(const ShunLib::Vec3& pos) { *m_pos = pos; }
	ShunLib::Vec3& Pos() { return *m_pos; }
};