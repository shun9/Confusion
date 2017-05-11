//************************************************/
//* @file  :SummonMagic.h
//* @brief :敵を召喚する魔法陣クラス
//* @date  :2017/05/10
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "../Wrapper/Texture/Texture.h"

class SummonMagic
{
private:
	ShunLib::Texture* m_texture;
	ShunLib::Effect* m_summonEffect;

	//位置
	ShunLib::Vec3* m_pos;

	//拡大率,最大拡大率（パワー）
	float m_scale;
	float m_maxScale;


	bool m_isStart;

	//回転用角度
	float m_angle;

	//召喚間隔 
	const int m_interval;
	int m_intervaCnt;

	//開始までの待ち時間
	const int m_firstInterval;
	int m_firstIntervaCnt;

public:
	SummonMagic(ShunLib::Vec3 pos = ShunLib::Vec3(0.0f, 0.0f, 0.0f), int interval = 60, int firstInterval=0,float scale = 5.0f);
	~SummonMagic();
	
	std::shared_ptr<Enemy> Create();
	void Update();

	void Draw(const ShunLib::Matrix& view,
			  const ShunLib::Matrix& proj);

	//召喚可能かどうか返す
	bool CanSummon()
	{
		if (m_scale <= 0.0f) { return false; }
		return (m_intervaCnt > m_interval);
	}

	//拡大率（パワー）
	void Scale(float scale) { m_scale = scale; }
	float Scale() { return m_scale; }

	//召喚開始しているかどうか
	bool IsStarted() { return m_isStart; }
};
