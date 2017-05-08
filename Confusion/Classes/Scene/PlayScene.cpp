//************************************************/
//* @file  :PlayScene.cpp
//* @brief :プレイ画面のソース
//* @date  :2017/05/01
//* @author:S.Katou
//************************************************/
#include <random>
#include "PlayScene.h"
#include "../Wrapper/Vec3/Vec3.h"
#include "../GameMain.h"
#include "../Conversion/Conversion.h"

//ステージの上下左右
const float PlayScene::STAGE_TOP = 20.0f;
const float PlayScene::STAGE_BOTTOM = -60.0f;
const float PlayScene::STAGE_RIGHT = 15.0f;
const float PlayScene::STAGE_LEFT = -15.0f;


//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//＋ーーーーーーーーーーーーーー＋
PlayScene::PlayScene()
{
	using namespace ShunLib;
	m_view = Matrix::CreateLookAt(Vec3(0.0f, 30.0f, 40.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 200.0f);

	//プレイヤー生成  delete ー> ~PlayScene
	m_player	= new Player*[Player::MAX_PLAYER];
	m_player[0] = new Player(L"CModel\\Player.cmo", Vec3(-5.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\PlayerB.cmo", Vec3(5.0f, 0.0f, 0.0f), 0, RIGHT);


	//m_summonEffect = new ShunLib::Effect(L"Effect\\MAGICALxSPIRAL\\Magic.efk", 60);
	m_summonEffect = new ShunLib::Effect(L"Effect\\Magic.efk", 60);
	m_blastEffect = new ShunLib::Effect(L"Effect\\Blast.efk", 0,512);

	//ステージ生成
	m_stage = new Stage;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
PlayScene::~PlayScene()
{
	//プレイヤー削除
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		delete m_player;
	}
	delete[] m_player;

	//敵削除
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		delete m_enemy[i];
	}

	//ステージ削除
	delete m_stage;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::Update()
{
	//敵出現(仮)
	static int t = 0;
	t++;
	if (t > 120)
	{
		CreateEnemy();
		t = 0;
	}


	//プレイヤー更新
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->Update();
		m_player[i]->Clamp(STAGE_TOP, STAGE_BOTTOM, STAGE_RIGHT, STAGE_LEFT);
	}

	//敵更新
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		m_enemy[i]->Update();
		m_enemy[i]->Dead(STAGE_TOP, STAGE_BOTTOM, STAGE_RIGHT, STAGE_LEFT);
	}

	//当たり判定
	Collision();

	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		//死んでいたら敵を削除
		if (m_enemy[i]->IsDead())
		{
			//爆破エフェクト設定
			m_blastEffect->SetDraw(m_enemy[i]->Pos()+ ShunLib::Vec3(0.0f, 1.0f, 0.0f));
			//m_blastEffect->SetPos(ShunLib::Vec3(0.0f,1.0f,0.0f));

			//敵削除
			delete m_enemy[i];
			m_enemy.erase(m_enemy.begin() + i);

			//ずれた分戻す
			i--;
		}
	}
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::Render()
{
	//ステージ描画
	m_stage->Draw(m_view, m_proj);

	//重力描画
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->DrawGravity(m_view, m_proj);
	}

	//プレイヤー描画
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		if (m_player[i]->InvincibleTime() % 2 == 0)
		{
			m_player[i]->Draw(m_view, m_proj);
		}
		m_player[i]->DrawHpGauge(m_view, m_proj);
	}

	m_summonEffect->Draw(m_view, m_proj);
	m_blastEffect->Draw(m_view, m_proj);

	//敵描画
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		m_enemy[i]->Draw(m_view,m_proj);
	}
}



//＋ーーーーーーーーーーーーーー＋
//｜機能  :当たり判定
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::Collision()
{
	//当たり判定
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		//敵と重力が当たっているかどうか
		bool isHitGravity[2] = { false,false };

		for (int j = 0; j < Player::MAX_PLAYER; j++)
		{
			//敵と重力の当たり判定
			isHitGravity[j] = Collision(m_enemy[i], m_player[j]->GetGravity());

			//プレイヤーが無敵ならば当たり判定を飛ばす
			if (m_player[j]->InvincibleTime() > 0){	break;}

			//敵とプレイヤーの当たり判定
			if (Collision(m_enemy[i], m_player[j]))
			{
				m_player[j]->TakeDamage(1);
				m_player[j]->InvincibleTime(60);
			}
		}

		//敵同士の当たり判定
		for (int j = i + 1; j < static_cast<int>(m_enemy.size()); j++)
		{
			if (Collision(m_enemy[i], m_enemy[j]))
			{
				//どちらかが混乱状態ならば両死
				if (m_enemy[i]->IsConfused() || m_enemy[j]->IsConfused())
				{
					m_enemy[i]->Dead();
					m_enemy[j]->Dead();
				}
			}
		}

		//挟み撃ちの処理
		if (IsSandwiched(isHitGravity, m_enemy[i])) { m_enemy[i]->Fluster(); }
	}
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :オブジェクト同士の当たり判定
//｜引数  :オブジェクト１(Object*)
//｜引数  :オブジェクト２(Object*)
//｜戻り値:当たっていたら true(bool)
//＋ーーーーーーーーーーーーーー＋
bool PlayScene::Collision(Object* obj,Object* obj2)
{
	using namespace ShunLib;

	Vec3 pos1 = obj->Pos();
	Vec3 pos2 = obj2->Pos();

	float x = pos1.m_x - pos2.m_x;
	float y = pos1.m_z - pos2.m_z;
	float r = obj->Radius() + obj2->Radius();

	if (x*x + y*y <= r*r){
		return true;
	}

	return false;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :重力との当たり判定
//｜引数  :オブジェクト(Object*)
//｜引数  :重力		   (Gravity*)
//｜戻り値:当たっていたら true(bool)
//＋ーーーーーーーーーーーーーー＋
bool PlayScene::Collision(Object* obj, Gravity* gra)
{
	using namespace ShunLib;

	Vec3 pos1 = obj->Pos();
	Vec3 pos2 = gra->Pos();

	float x = pos1.m_x - pos2.m_x;
	float y = pos1.m_z - pos2.m_z;
	float r = obj->Radius() + gra->Radius();

	if (x*x + y*y <= r*r){
		//対象を重力で引き寄せる
		ShunLib::Vec3 pos = obj->Pos();
		gra->Attract(&pos);
		obj->Pos(pos);
		return true;
	}

	return false;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :挟まれているかどうかの判定
//｜引数  :重力との当たり判定の結果(bool[])
//｜戻り値:挟まれていたらtrue(bool)
//＋ーーーーーーーーーーーーーー＋
bool PlayScene::IsSandwiched(bool isHitGravity[], Enemy* enemy)
{
	using namespace ShunLib;

	int hitNum = 0;

	//当たっている数をカウント
	for (int i = 0; i < Player::MAX_PLAYER; i++){
		if (isHitGravity[i]) { hitNum++; }
	}

	//１or０ならば抜ける
	if (hitNum <= 1) { return false; }


	//ベクトルを求める
	Vec3 v1 = m_player[0]->Pos() - enemy->Pos();
	Vec3 v2 = m_player[1]->Pos() - enemy->Pos();

	//正規化
	v1.Normalize();
	v2.Normalize();

	//内積を求める
	float dot = v1.GetDirectVec3().Dot(v2.GetDirectVec3());

	//角度を求める
	float angle = ToAngle(acos(dot));

	//角度が一定以上なら挟まれている
	if (std::abs(angle) >= 90.0f)
	{
		return true;
	}

	return false;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :敵の生成
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::CreateEnemy()
{
	//乱数生成用
	std::random_device random;
	std::mt19937 mt(random());

	//乱数の値を制限
	std::uniform_real_distribution<float> num(STAGE_LEFT, STAGE_RIGHT);

	//敵生成　delete ー> ~PlayScene
	m_enemy.push_back(new Enemy(L"CModel\\Enemy.cmo", ShunLib::Vec3(num(mt), 0.0f,STAGE_BOTTOM),ShunLib::Vec3(0.0f,0.0f,0.1f)));

	m_summonEffect->SetDraw();
	m_summonEffect->SetScale(1.5f);
	m_summonEffect->SetPos(m_enemy.back()->Pos());
}

