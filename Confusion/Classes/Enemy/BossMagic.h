//************************************************/
//* @file  :BossMagic.h
//* @brief :�G����������{�X���@�w�N���X
//* @date  :2017/05/17
//* @author:S.Katou
//************************************************/
#pragma once
#include "SummonMagic.h"

class BossMagic : public SummonMagic
{
private:
	int m_hp;
	bool m_isDead;

public:
	BossMagic(ShunLib::Vec3 pos = ShunLib::Vec3(0.0f, 0.0f, 0.0f), int interval = 60, int firstInterval = 0, float scale = 5.0f, int hp = 100);
	~BossMagic();

	//�G�̐���
	std::shared_ptr<Enemy> SummonEnemy()override;
	std::shared_ptr<SummonMagic> CreateMagic(float stageX, float stageW, float stageY,float stageH);

	//�`��
	void Draw(const ShunLib::Matrix& view,
			  const ShunLib::Matrix& proj)override;
	
	//�_���[�W���󂯂�
	void TakeDamage(int damage);

	//����
	void Dead() { m_isDead = true; }

	//���擾�֘A
	int HP() { return m_hp; }
	bool IsDead() { return m_isDead; }
};