//************************************************/
//* @file  :SummonMagic.cpp
//* @brief :敵を召喚する魔法陣クラス
//* @date  :2017/05/10
//* @author:S.Katou
//************************************************/
#include "SummonMagic.h"
#include <random>
#include "../Timer/Timer.h"
#include "../RandomNumber/RandomNumber.h"

SummonMagic::SummonMagic(ShunLib::Vec3 pos, int interval, int firstInterval, float scale, float summonPower)
	: m_scale(0.0f)
	, m_maxScale(scale)
	, m_angle(0.0f)
	, m_isStart(false)
	, m_summonPower(summonPower)
{
	using namespace ShunLib;
	m_texture	   = new Texture(L"Images\\magic.png");
	m_pos          = new Vec3(pos);
	m_summonEffect = new Effect(L"Effect\\Magic.efk",60);
	m_summonIntervalTimer = new Timer();
	m_summonIntervalTimer->SetTime(interval);
	m_firstIntervalTimer = new Timer();
	m_firstIntervalTimer->SetTime(firstInterval);
}

SummonMagic::~SummonMagic()
{
	delete m_texture;
	delete m_pos;
	delete m_summonEffect;

	delete m_summonIntervalTimer;
	delete m_firstIntervalTimer;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :敵を生成する
//｜引数  :なし(void)
//｜戻り値:敵(shared_ptr<Enemy>)
//＋ーーーーーーーーーーーーーー＋
std::shared_ptr<Enemy> SummonMagic::SummonEnemy()
{
	using namespace ShunLib;

	RandomNumber randNum;
	Vec3 randPos(randNum(-m_scale,m_scale),0.0f, randNum(-m_scale, m_scale));
	Vec3 randSpd(0.0f, 0.0f, randNum(0.1f, 100.0f));

	//敵生成
	std::shared_ptr<Enemy>enemy = std::make_shared<Enemy>(L"CModel\\Enemy.cmo",
								  *m_pos+ randPos,
		randSpd);
	
	//エフェクト設定
	m_summonEffect->SetDraw();
	m_summonEffect->SetScale(2.0f);
	m_summonEffect->SetPos(enemy->Pos());

	//カウントリセット
	m_summonIntervalTimer->ResetCount();

	//パワーダウン
	m_scale -= m_summonPower;

	return enemy;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void SummonMagic::Update()
{
	//開始まで待つ
	if (!(m_firstIntervalTimer->IsEnded()))
	{
		m_firstIntervalTimer->Update();
		return;
	}

	//回転
	m_angle += 1.0f;
	if (m_angle >= 360.0f)
	{
		m_angle = 0.0f;
	}

	//召喚開始まで待つ
	if (m_isStart)
	{
		m_summonIntervalTimer->Update();
	}

	if (!m_isStart)
	{
		m_scale += 0.1f;
		if (m_scale >= m_maxScale)
		{
			m_isStart = true;
		}
	}
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :ビュー行列		   (ShunLib::Matrix)
//｜引数  :プロジェクション行列(ShunLib::Matrix)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void SummonMagic::Draw(const ShunLib::Matrix& view, const ShunLib::Matrix& proj)
{
	using namespace ShunLib;

	Matrix world;
	world = Matrix::CreateScale(m_scale * 2)
		  * Matrix::CreateRotationY(m_angle)
		  * Matrix::CreateTranslation(*m_pos+Vec3(0.0f,1.0f,0.0f));

	m_texture->Draw(world, view, proj);

	m_summonEffect->Draw(view, proj);
}
