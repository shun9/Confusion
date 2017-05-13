//************************************************/
//* @file  :PlayScene.cpp
//* @brief :プレイ画面のクラス
//* @date  :2017/05/13
//* @author:S.Katou
//************************************************/
#include <random>
#include "PlayScene.h"
#include "../Sound/PlayScene.h"
#include "../Sound/ADX2Le.h"
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
	:m_isStarted(false)
	,m_isEnded(false)
	,m_stageLife(5)
{
	using namespace ShunLib;
	m_view = Matrix::CreateLookAt(Vec3(0.0f, 30.0f, 40.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 200.0f);

	m_hpGauge = new HPGauge(m_stageLife, Vec3(0.0f, 1.0f, 21.2f), Vec3(27.5f, 1.0f, 2.0f), Vec3(-55.0f, 0.0f, 0.0f));

	//プレイヤー生成  delete ー> ~PlayScene
	m_player	= new Player*[Player::MAX_PLAYER];
	m_player[0] = new Player(L"CModel\\Player.cmo", Vec3(-5.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\PlayerB.cmo", Vec3(5.0f, 0.0f, 0.0f), 0, RIGHT);

	//爆破エフェクト生成
	m_blastEffect = new ShunLib::Effect(L"Effect\\Blast.efk", 0,512);
	
	//魔法陣の数をランダムで決定
	m_maxMagic = rand() % 5 + 2;
	
	//魔法陣の生成  delete ー> ~PlayScene
	m_magic = new SummonMagic*[m_maxMagic];
	for (int i = 0; i < m_maxMagic; i++)
	{
		m_magic[i] = new SummonMagic(Vec3(static_cast<float>(std::rand() % 20-10.0f),0.0f, -(static_cast<float>(std::rand() % 40 + 10))),
									 rand()%500+30,
									 i*20,5.0f);
	}

	//ステージ生成
	m_stage = new Stage;

	ADX2Le::LoadAcb("Sounds\\PlayScene.acb");
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
PlayScene::~PlayScene()
{
	//プレイヤー削除
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		if (m_player[i] != nullptr) { delete m_player[i]; }
	}
	if (m_player != nullptr) { delete[] m_player; }

	//魔法陣の削除
	for (int i = 0; i < m_maxMagic; i++)
	{
		if (m_magic[i] != nullptr) { delete m_magic[i]; }
	}
	if (m_magic != nullptr) { delete[] m_magic; }

	//ステージ削除
	if (m_stage != nullptr){ delete m_stage; }
	
	//HPゲージ削除
	if (m_hpGauge != nullptr) { delete m_hpGauge; }	
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::Update()
{
	//プレイ前の処理
	if (!m_isStarted)
	{
		PlayAgo();
	}

	//プレイ中の処理
	if (m_isStarted
	&& !m_isEnded)
	{
		PlayMain();
	}


	//ゲームオーバー
	if (IsGameOver())
	{
		if (PlayGameOver())
		{
			m_nextScene = Scene::OVER;
		}
	}

	//ゲームクリア
	if (IsCleared())
	{
		if (PlayClear())
		{
			m_nextScene = Scene::CLEAR;
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

	//魔法陣描画
	for (int i = 0; i < m_maxMagic; i++)
	{
		m_magic[i]->Draw(m_view, m_proj);
	}

	//エフェクト表示
	m_blastEffect->Draw(m_view, m_proj);

	//プレイヤー描画
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		if (m_player[i]->InvincibleTime() % 2 == 0)
		{
			m_player[i]->Draw(m_view, m_proj);
		}
		m_player[i]->DrawHpGauge(m_view, m_proj);
	}

	//敵描画
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		m_enemy[i]->Draw(m_view,m_proj);		
	}

	//ＨＰゲージ描画
	m_hpGauge->HP(m_stageLife);
	m_hpGauge->Draw(m_view, m_proj);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :プレイ開始前の処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::PlayAgo()
{
	m_isStarted = true;
	for (int i = 0; i < m_maxMagic; i++)
	{
		//魔法陣更新
		m_magic[i]->Update();
		
		//魔法陣が出現していなかったら始まらない
		if (!m_magic[i]->IsStarted())
		{
			m_isStarted = false;
		}
	}
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :プレイ中の処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::PlayMain()
{

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
		
		//敵が下に当たって死んだらダメージ	
		if (m_enemy[i]->Dead(STAGE_TOP, STAGE_BOTTOM, STAGE_RIGHT, STAGE_LEFT) == ShunLib::DIRECTION_2D::BOTTOM)
		{
			m_stageLife--;
		}
		
		//死んでいた時の処理
		if (m_enemy[i]->IsDead())
		{
			//爆破エフェクト設定
			m_blastEffect->SetDraw(m_enemy[i]->Pos() + ShunLib::Vec3(0.0f, 1.0f, 0.0f));
			ADX2Le::Play(CRI_PLAYSCENE_BOMB2);

			//敵削除
			m_enemy.erase(m_enemy.begin() + i);

			//ずれた分戻す
			i--;
		}
	}

	//魔法陣更新
	for (int i = 0; i < m_maxMagic; i++)
	{
		m_magic[i]->Update();
	}

	//敵生成
	CreateEnemy();

	//当たり判定
	Collision();
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :クリアの処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
bool PlayScene::PlayClear()
{
	m_isEnded = true;
	static int b = 0;
	b++;
	if (b < 260)
	{
		return false;
	}
	return true;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :ゲームオーバーの処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
bool PlayScene::PlayGameOver()
{
	m_isEnded = true;

	static int a = 0;
	a++;
	if (a < 260)
	{
		return false;
	}
	return true;
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
			isHitGravity[j] = Collision(m_enemy[i].get(), m_player[j]->GetGravity());

			//プレイヤーが無敵ならば当たり判定を飛ばす
			if (m_player[j]->InvincibleTime() > 0){	break;}

			//敵とプレイヤーの当たり判定
			if (Collision(m_enemy[i].get(), m_player[j]))
			{
				m_player[j]->TakeDamage(1);
				m_player[j]->InvincibleTime(60);

				m_enemy[i]->Dead();
			}
		}

		//敵同士の当たり判定
		for (int j = i + 1; j < static_cast<int>(m_enemy.size()); j++)
		{
			if (Collision(m_enemy[i].get(), m_enemy[j].get()))
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
		if (IsSandwiched(isHitGravity, m_enemy[i].get())) { m_enemy[i]->Fluster(); }
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

	if (x*x + y*y <= r*r)
	{
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
	if (std::abs(angle) >= 80.0f)
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
	for (int i = 0; i < m_maxMagic; i++)
	{
		//魔法陣が召喚可能ならば敵召喚
		if (m_magic[i]->CanSummon())
		{
			m_enemy.push_back(m_magic[i]->Create());
		}
	}
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :ゲームクリア判定
//｜引数  :なし(void)
//｜戻り値:クリアしたらtrue(bool)
//＋ーーーーーーーーーーーーーー＋
bool PlayScene::IsCleared()
{
	for (int i = 0; i < m_maxMagic; i++)
	{
		//魔法陣が一つでも存在していたらNOT CLEAR
		if (m_magic[i]->Scale() > 0.0f)
		{
			return false;
		}
	}

	//敵が存在していたらNOT CLEAR
	if (!m_enemy.empty())
	{
		return false;
	}
	return true;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :ゲームオーバー判定
//｜引数  :なし(void)
//｜戻り値:ゲームオーバーでtrue(bool)
//＋ーーーーーーーーーーーーーー＋
bool PlayScene::IsGameOver()
{
	//プレイヤーが片方でも死んだらGameOver
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		if (m_player[i]->Hp() <= 0)
		{
			return true;
		}
	}

	//ステージのライフが０になったらGameOver
	if (m_stageLife <= 0)
	{
		return true;
	}
	return false;
}


