//************************************************/
//* @file  :SummonMagic.h
//* @brief :敵を召喚する魔法陣クラス
//* @date  :2017/05/18
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "../Wrapper/Texture/Texture.h"
#include "../Wrapper/Model/Model.h"
#include "../Timer/Timer.h"

class SummonMagic
{
protected:
	static std::unique_ptr<ShunLib::Texture> m_texture;
	static std::unique_ptr<ShunLib::Effect> m_summonEffect;

	//位置
	ShunLib::Vec3* m_pos;

	//拡大率,最大拡大率（パワー）
	float m_scale;
	float m_maxScale;

	//召喚開始したらtrue
	bool m_isStart;

	//回転用角度
	float m_angle;

	//召喚間隔
	ShunLib::Timer* m_summonIntervalTimer;


	//召喚開始までの待ち時間
	ShunLib::Timer* m_firstIntervalTimer;

	//召喚に必要なパワー
	float m_summonPower;

public:
	SummonMagic(ShunLib::Vec3 pos = ShunLib::Vec3(0.0f, 0.0f, 0.0f), int interval = 60, int firstInterval = 0, float scale = 5.0f, float summonPower = 1.0f);
	~SummonMagic();

	//敵の生成
	virtual std::shared_ptr<Enemy> SummonEnemy();

	//更新処理
	void Update();

	//描画
	virtual void Draw(const ShunLib::Matrix& view,
					  const ShunLib::Matrix& proj);

	//召喚可能かどうか返す
	bool CanSummon()
	{
		if (m_scale <= 0.0f){
			return false;
		}

		return (m_summonIntervalTimer->IsEnded());
	}

	//拡大率（パワー）
	void Scale(float scale) { m_scale = scale; }
	float Scale() { return m_scale; }

	//召喚開始しているかどうか
	bool IsStarted() { return m_isStart; }

protected:
	void DrawSummonEffect(const ShunLib::Vec3& pos);
};
