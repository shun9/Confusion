//************************************************/
//* @file  :PlayScene.cpp
//* @brief :プレイ画面のクラス
//* @date  :2017/05/17
//* @author:S.Katou
//************************************************/
#include <random>
#include "PlayScene.h"
#include "../Sound/PlayScene.h"
#include "../Sound/TitleScene.h"
#include "../Sound/ADX2Le.h"
#include "../Wrapper/Vec3/Vec3.h"
#include "../GameMain.h"
#include "../Conversion/Conversion.h"
#include "../Enemy/BossMagic.h"

//ステージの上下左右
const float PlayScene::STAGE_TOP    =  25.0f;
const float PlayScene::STAGE_BOTTOM = -30.0f;
const float PlayScene::STAGE_RIGHT  =  15.0f;
const float PlayScene::STAGE_LEFT   = -15.0f;


//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//＋ーーーーーーーーーーーーーー＋
PlayScene::PlayScene()
	:m_isStarted(false)
	,m_isEnded(false)
	,m_stageHP(300)
{
	using namespace ShunLib;
	m_view = Matrix::CreateLookAt(Vec3(0.0f, 30.0f, 50.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 200.0f);


	//プレイヤー生成  delete ー> ~PlayScene
	m_player	= new Player*[Player::MAX_PLAYER];
	m_player[0] = new Player(L"CModel\\Player.cmo", Vec3(-5.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\PlayerB.cmo", Vec3(5.0f, 0.0f, 0.0f), 0, RIGHT);

	//エフェクト生成
	m_blastEffect = new ShunLib::Effect(L"Effect\\Blast.efk", 0, 512*2);
	m_endEffect = new ShunLib::Effect(L"Effect\\GameClear2.efk", 120, 512);

	//ボス魔法陣生成
	m_boss = std::make_unique<BossMagic>(ShunLib::Vec3(0.0f, 0.0f, STAGE_BOTTOM), 90, 0, 15.0f, 500);

	m_hpGauge = new HPGauge(m_stageHP, Vec3(0.0f, 0.0f, 26.7f), Vec3(29.5f, 1.0f, 2.0f), Vec3(-55.0f, 0.0f, 0.0f));
	m_bossGauge = new HPGauge(m_boss->HP(), Vec3(0.0f, 26.0f, 26.7f), Vec3(10.5f, 0.8f, 1.0f), Vec3(-55.0f, 0.0f, 0.0f));

	//ステージ生成
	m_stage = new Stage;

	m_createMagicTimer = new Timer();
	m_createMagicTimer->SetTime(600);

	ADX2Le::LoadAcb("Sounds\\PlayScene.acb", "Sounds\\PlayScene.awb");
	ADX2Le::Play(CRI_PLAYSCENE_DAMONS_DANCE);
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


	//ステージ削除
	if (m_stage != nullptr) { delete m_stage; }

	//HPゲージ削除
	if (m_hpGauge != nullptr) { delete m_hpGauge; }
	if (m_bossGauge != nullptr) { delete m_bossGauge; }

	//エフェクト削除
	if (m_blastEffect != nullptr) { delete m_blastEffect; }
	if (m_endEffect != nullptr) { delete m_endEffect; }
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
	if (m_isStarted)
	{
		if (!m_isEnded)
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
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::Render()
{
	//ステージの描画
	DrawStage();

	//魔法陣描画
	std::vector<std::shared_ptr<SummonMagic>>::iterator magicItr;
	for (magicItr = m_magic.begin(); magicItr != m_magic.end(); magicItr++)
	{
		(*magicItr)->Draw(m_view, m_proj);
	}

	//重力描画（描画順の関係でPlayerと分ける）
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->DrawGravity(m_view, m_proj);
	}

	//エフェクト表示
	if (m_blastEffect != nullptr){	m_blastEffect->Draw(m_view, m_proj);}


	//プレイヤー描画
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->Draw(m_view, m_proj);
	}

	//敵描画
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++){	m_enemy[i]->Draw(m_view,m_proj);}

	//ＨＰゲージ描画
	if (m_stageHP > 0)
	{
		m_hpGauge->HP(m_stageHP);
		m_hpGauge->Draw(m_view, m_proj);
	}

	//ボス魔法陣が存在する間ＨＰゲージを表示
	if (!(m_boss->IsDead()))
	{
		m_bossGauge->HP(m_boss->HP());
		m_bossGauge->Draw(m_view, m_proj);
	}

	//エフェクト描画
	if (!m_endEffect->IsEnded())   { m_endEffect->Draw(m_view, m_proj); }
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :敵関連の更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::UpdateEnemy()
{
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		m_enemy[i]->Update();
		int dir = m_enemy[i]->Dead(STAGE_TOP, STAGE_BOTTOM, STAGE_RIGHT, STAGE_LEFT);
		//敵が下に当たって死んだらダメージ	
		if (dir == ShunLib::DIRECTION_2D::BOTTOM)
		{
			m_stageHP--;
		}
		//敵が下に当たって死んだらボス魔法陣にダメージ	
		if (dir == ShunLib::DIRECTION_2D::TOP)
		{
			m_boss->TakeDamage(20);
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
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :魔法陣関連の更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::UpdateMagic()
{
	//魔法陣更新
	std::vector<std::unique_ptr<SummonMagic>>::iterator magicItr;
	for (int i = 0; i < static_cast<int>(m_magic.size()); i++)
	{
		m_magic[i]->Update();
		if (!(m_magic[i]->IsStarted())) { continue; }

		if (m_magic[i]->CanSummon())
		{
			m_enemy.push_back(m_magic[i]->SummonEnemy());
		}

		if (m_magic[i]->Scale() <= 0.0f) { m_magic.erase(m_magic.begin() + i); i--; }
	}

	//一定時間ごとに魔法陣召喚）
	if (m_createMagicTimer->IsEnded())
	{
		m_createMagicTimer->ResetCount();
		m_magic.push_back(m_boss->CreateMagic(STAGE_LEFT,STAGE_RIGHT,0.0f,STAGE_BOTTOM));
	}
	m_boss->Update();
	if (m_boss->CanSummon()) { m_enemy.push_back(m_boss->SummonEnemy()); }

}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :ステージ関連の描画処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::DrawStage()
{
	//ステージ描画　
	//間にボス魔法陣を挟む
	using namespace ShunLib;
	using namespace std;

	//ステージ奥描画
	Matrix stageScale = Matrix::CreateScale(Vec3(120.0f, 1.0f, abs(STAGE_BOTTOM) * 2));
	m_stage->Draw(stageScale*Matrix::CreateTranslation(Vec3(0.0f, 0.0f, STAGE_BOTTOM)), m_view, m_proj);

	if (m_boss != nullptr)
	{
		m_boss->Draw(m_view, m_proj);
	}

	//ステージ描画 表示がバグるので少しだけずらす
	m_stage->Draw(stageScale*Matrix::CreateTranslation(Vec3(0.0f, 0.01f, 0.0f)), m_view, m_proj);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :プレイ開始前の処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::PlayAgo()
{
	m_isStarted = true;
	m_boss->Update();
	if (!(m_boss->IsStarted()))
	{
		m_isStarted = false;
		return;
	}

	std::vector<std::shared_ptr<SummonMagic>>::iterator magicItr;
	for (magicItr = m_magic.begin(); magicItr != m_magic.end(); magicItr++)
	{
		//魔法陣更新
		(*magicItr)->Update();
		
		//魔法陣が出現していなかったら始まらない
		if (!((*magicItr)->IsStarted()))
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
	UpdateEnemy();

	//魔法陣更新
	UpdateMagic();

	//タイマーカウント
	m_createMagicTimer->Update();

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

	if (m_endEffect->IsEnded())
	{
		return true;
	}
	return false;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :ゲームオーバーの処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
bool PlayScene::PlayGameOver()
{
	m_isEnded = true;

	if (m_endEffect->IsEnded())
	{
		return true;
	}
	return false;
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
				ADX2Le::Play(CRI_PLAYSCENE_BOMB2);
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
//｜機能  :魔法陣の生成
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::CreateMagic()
{	
	float randPosX = static_cast<float>(std::rand() % std::abs((int)(STAGE_RIGHT + STAGE_LEFT + 1)));
	float randPosZ= -(static_cast<float>(std::rand() % std::abs((int)STAGE_BOTTOM)));
	int summonInterval = std::rand() % 500 + 30;
	int firstInterval = std::rand() % 120 + 120;
	float scale = (rand() % 100 + 1) / 10.0f;

	m_magic.push_back(std::make_unique<SummonMagic>(
		ShunLib::Vec3(randPosX,0.0f,randPosZ),
		summonInterval,
		firstInterval,
		scale));
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :すべての魔法陣を消す
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::DeleteAllMagic()
{
	//敵の削除
	while (!m_enemy.empty())
	{
		std::shared_ptr<Enemy> enemy = m_enemy.back();

		//爆破エフェクト設定
		m_blastEffect->SetDraw(enemy->Pos() + ShunLib::Vec3(0.0f, 1.0f, 0.0f));
		ADX2Le::Play(CRI_PLAYSCENE_BOMB2);
		m_enemy.pop_back();
	}

	//魔法陣の削除
	while (!m_magic.empty())
	{
		m_magic.pop_back();
	}
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :ゲームクリア判定
//｜引数  :なし(void)
//｜戻り値:クリアしたらtrue(bool)
//＋ーーーーーーーーーーーーーー＋
bool PlayScene::IsCleared()
{
	//ボスのＨＰが０になったらクリア
	if (m_boss->HP() <= 0)
	{
		if (!m_isEnded)
		{
			//全ての魔法陣を消す
			DeleteAllMagic();

			//ボス死ぬ
			m_boss->Dead();

			//エフェクト再生
			m_endEffect->SetDraw(ShunLib::Vec3(0.0f, 1.0f, STAGE_BOTTOM));
			m_endEffect->SetScale(8.0f);
			m_endEffect->SetSpd(0.3f);

			//効果音
			ADX2Le::Play(CRI_PLAYSCENE_MAGIC_CHANT2);
			m_isEnded = true;
		}		
		return true;
	}
	return false;
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
			if (!m_isEnded)
			{
				m_endEffect->SetDraw(m_player[i]->Pos());
				m_endEffect->SetScale(1.5f);
				m_endEffect->SetSpd(0.5f);
				ADX2Le::Play(CRI_PLAYSCENE_MAGIC_CHANT2);

				m_isEnded = true;
			}
			return true;
		}
	}

	//ステージのライフが０になったらGameOver
	if (m_stageHP <= 0)
	{
		if (!m_isEnded)
		{
			ADX2Le::Play(CRI_PLAYSCENE_MAGIC_CHANT2);

			//エフェクト再生
			m_endEffect->SetDraw(ShunLib::Vec3(0.0f, 1.0f, STAGE_TOP));
			m_endEffect->SetScale(8.0f);
			m_endEffect->SetSpd(0.3f);

			m_isEnded = true;
		}
		return true;
	}
	return false;
}


