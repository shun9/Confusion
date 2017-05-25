//************************************************/
//* @file  :BossMagic.cpp
//* @brief :敵を召喚するボス魔法陣クラス
//* @date  :2017/05/17
//* @author:S.Katou
//************************************************/
#include "BossMagic.h"
#include "../RandomNumber/RandomNumber.h"


BossMagic::BossMagic(ShunLib::Vec3 pos, int interval, int firstInterval, float scale,int hp)
	:SummonMagic(pos,interval,firstInterval,scale)
	,m_hp(hp)
	, m_isDead(false)
{
}

BossMagic::~BossMagic()
{
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :敵を生成する
//｜引数  :なし(void)
//｜戻り値:敵(shared_ptr<Enemy>)
//＋ーーーーーーーーーーーーーー＋
std::shared_ptr<Enemy> BossMagic::SummonEnemy()
{
	using namespace ShunLib;

	RandomNumber randNum;
	Vec3 randPos(randNum(-m_scale, m_scale), 0.0f, 1.0f);
	Vec3 randSpd(0.0f, 0.0f, randNum(0.1f, 100.0f));

	//敵生成
	std::shared_ptr<Enemy>enemy = std::make_shared<Enemy>(L"CModel\\Enemy.cmo",
		*m_pos + randPos,randSpd);

	//エフェクト設定
	DrawSummonEffect(enemy->Pos());

	//カウントリセット
	m_summonIntervalTimer->ResetCount();

	//パワーダウン
	m_hp--;

	return enemy;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :ビュー行列		   (ShunLib::Matrix)
//｜引数  :プロジェクション行列(ShunLib::Matrix)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void BossMagic::Draw(const ShunLib::Matrix & view, const ShunLib::Matrix & proj)
{
	if (m_isDead)
	{
		return;
	}

	using namespace ShunLib;

	Matrix world;
	world = Matrix::CreateScale(m_scale * 2)
		  * Matrix::CreateRotationY(m_angle)
		  * Matrix::CreateRotationX(90.0f)
		  * Matrix::CreateTranslation(*m_pos);

	m_texture->Draw(world, view, proj);

	m_summonEffect->Draw(view, proj);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :ダメージを受ける
//｜引数  :ダメージ(int)
//｜戻り値:なし　　(void)
//＋ーーーーーーーーーーーーーー＋
void BossMagic::TakeDamage(int damage) {
	m_hp -= damage;
	if (m_hp < 0) { m_hp = 0; }
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :魔法陣の生成
//｜引数  :ステージの左端(float)
//｜引数  :ステージの上端(float)
//｜引数  :ステージの幅　(float)
//｜引数  :ステージの高さ(float)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
std::shared_ptr<SummonMagic> BossMagic::CreateMagic(float stageX, float stageW, float stageY, float stageH)
{
	using namespace ShunLib;

	//乱数生成
	RandomNumber randNum;

	//大きさ
	float scale = randNum(0.1f, 5.0f);

	//位置 魔法陣が収まる位置に生成
	float posX = stageX > stageW ? randNum(stageW + scale, stageX - scale) : randNum(stageX + scale, stageW - scale);
	float posZ = stageY > stageH ? randNum(stageH + scale, stageY - scale) : randNum(stageY + scale, stageH - scale);
	Vec3 pos(posX,0.0f, posZ);

	//召喚間隔
	int summonInterval = randNum(60,500);

	//動き始めるまでの時間
	int firstInterval = randNum(100,200);


	std::shared_ptr<SummonMagic> magic;
	magic = std::make_shared<SummonMagic>(pos, summonInterval, firstInterval, scale);

	return magic;
}