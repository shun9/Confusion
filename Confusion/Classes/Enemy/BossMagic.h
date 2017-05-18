//************************************************/
//* @file  :BossMagic.h
//* @brief :敵を召喚するボス魔法陣クラス
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

	//敵の生成
	std::shared_ptr<Enemy> SummonEnemy()override;
	std::shared_ptr<SummonMagic> CreateMagic(float stageX, float stageW, float stageY,float stageH);

	//描画
	void Draw(const ShunLib::Matrix& view,
			  const ShunLib::Matrix& proj)override;
	
	//ダメージを受ける
	void TakeDamage(int damage);

	//死ぬ
	void Dead() { m_isDead = true; }

	//情報取得関連
	int HP() { return m_hp; }
	bool IsDead() { return m_isDead; }
};