//************************************************/
//* @file  :PlayScene.cpp
//* @brief :プレイ画面のソース
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#include "PlayScene.h"
#include "../Wrapper/Vec3/Vec3.h"
#include "../GameMain.h"

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//＋ーーーーーーーーーーーーーー＋
PlayScene::PlayScene()
{
	using namespace ShunLib;
	m_view = Matrix::CreateLookAt(Vec3(0.0f, 10.0f, 13.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(90.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 100.0f);

	//プレイヤー生成  delete ー> ~PlayScene
	m_player = new Player*[Player::MAX_PLAYER];
	m_player[0] = new Player(L"CModel\\Player.cmo", Vec3(-5.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\PlayerB.cmo", Vec3(5.0f, 0.0f, 0.0f), 0, RIGHT);

	//敵生成　delete ー> ~PlayScene
	m_enemy.push_back(new Enemy(L"CModel\\Enemy.cmo", Vec3(0.0f, 0.0f, 5.0f)));
	m_enemy.push_back(new Enemy(L"CModel\\Enemy.cmo", Vec3(0.0f, 0.0f, -5.0f)));
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
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::Update()
{

	//プレイヤー更新
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->Update();
	}

	//敵更新
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		m_enemy[i]->Update();
	}


	Collision();
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::Render()
{
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
	}

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
		for (int j = 0; j < Player::MAX_PLAYER; j++)
		{
			//敵と重力の当たり判定
			if (Collision(m_enemy[i], m_player[j]->GetGravity()))
			{
				//敵を重力で引き寄せる
				ShunLib::Vec3 pos = m_enemy[i]->Pos();
				m_player[j]->GetGravity()->Attract(&pos);
				m_enemy[i]->Pos(pos);
			}

			//プレイヤーが無敵ならば当たり判定を飛ばす
			if (m_player[j]->InvincibleTime() > 0)
			{
				break;
			}

			//敵とプレイヤーの当たり判定
			if (Collision(m_enemy[i], m_player[j]))
			{
				m_player[j]->TakeDamage(1);
				m_player[j]->InvincibleTime(60);
			}
		}
	}
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :当たり判定
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
//｜機能  :当たり判定
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

	if (x*x + y*y <= r*r)
	{
		return true;
	}

	return false;
}

