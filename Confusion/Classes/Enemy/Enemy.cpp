//************************************************/
//* @file  :Enemy.cpp
//* @brief :敵のソースファイル
//* @date  :2017/05/06
//* @author:S.Katou
//************************************************/
#include "Enemy.h"
//速度倍率
const float Enemy::SPD_MAGNIFICATION = 3.0f;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//｜引数  :画像のパス(wchar_t*)
//｜引数  :初期座標	 (ShunLib::Vec3)
//＋ーーーーーーーーーーーーーー＋
Enemy::Enemy(const wchar_t* model, ShunLib::Vec3 pos, ShunLib::Vec3 spd)
	: Object(model,pos,spd)
	, m_isDead(false)
	, m_confusedTime(0)
	, m_isConfused(false)
{
	m_radius = 1.0f;
	m_firstSpd = spd;

	m_summonEffect = new ShunLib::Effect(L"Effect\\MAGICALxSPIRAL\\Magic.efk",60,true);
	m_summonEffect->SetScale(1.5f);
	m_summonEffect->SetPos(*m_pos);
	
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Enemy::~Enemy()
{
	delete m_summonEffect;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Enemy::Update()
{
	//移動
	*m_pos = *m_pos + (*m_spd * SPD_MAGNIFICATION / 60.0f);

	//混乱時間経過
	if (m_isConfused)
	{
		m_confusedTime--;
	}

	//時間経過で混乱状態解除
	if (m_confusedTime <= 0)
	{
		*m_spd = m_firstSpd;
		m_confusedTime = 0;
		m_isConfused = false;
	}
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画
//｜引数  :ビュー行列		   (ShunLib::Matrix)
//｜引数  :プロジェクション行列(ShunLib::Matrix)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Enemy::Draw(const ShunLib::Matrix& view, const ShunLib::Matrix& proj)
{
	using namespace ShunLib;
	
	Object::Draw(view,proj);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :速度ベクトルを回転させる
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Enemy::Fluster()
{
	m_isConfused = true;

	//速度ベクトルを回転させる
	m_spd->m_x = cosf(static_cast<float>(m_confusedTime/30));
	m_spd->m_z = sinf(static_cast<float>(m_confusedTime/30));

	//混乱時間を加算 0.5秒
	m_confusedTime += 30;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :範囲外に出たら死
//｜引数  :ステージの上(float)
//｜引数  :ステージの下(float)
//｜引数  :ステージの右(float)
//｜引数  :ステージの左(float)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Enemy::Dead(float top, float bottom, float right, float left)
{
	//Ｚ軸正側判定
	if (m_pos->m_z > top)
	{
		Dead();	
		return;
	}

	//Ｚ軸負側判定
	if (m_pos->m_z < bottom)
	{
		Dead();
		return;
	}


	//Ｘ軸正側判定
	if (m_pos->m_x > right)
	{
		Dead();
		return;
	}

	//Ｘ軸負側判定
	if (m_pos->m_x < left)
	{
		Dead();
		return;
	}
}
