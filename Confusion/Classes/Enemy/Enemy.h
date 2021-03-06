//************************************************/
//* @file  :Enemy.h
//* @brief :敵のヘッダーファイル
//* @date  :2017/05/23
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Object/Object.h"
#include "../Wrapper/Vec3/Vec3.h"
#include "../Wrapper/Effekseer/Effect.h"

class Enemy : public Object
{
private:
	//速度倍率
	static const float SPD_MAGNIFICATION;

private:
	//生死
	bool m_isDead;
	
	//混乱時間
	int m_confusedTime;

	//混乱しているかどうか
	bool m_isConfused;

	//最初の速度
	ShunLib::Vec3 m_firstSpd;

	//登場時のエフェクト
	ShunLib::Effect* m_confusionEffect;

public:
	Enemy(const wchar_t* model,
		ShunLib::Vec3 pos = (0.0f, 0.0f, 0.0f),
		ShunLib::Vec3 spd = (0.0f, 0.0f, 0.0f));
	~Enemy();

	//更新
	void Update()override;

	//描画処理
	void Draw(const ShunLib::Matrix& view,
			  const ShunLib::Matrix& proj);

	//混乱する
	void Fluster();

	//混乱しているかどうか
	bool IsConfused() { return m_isConfused; }
	
	//死
	void Dead() { m_isDead = true; }
	
	//範囲外に出たら死
	//出た方向を返す
	//出なかったら　-1
	int Dead(float top, float bottom, float right, float left);

	//死んでいるかどうか
	bool IsDead() { return m_isDead; }
};
