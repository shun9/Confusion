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

	m_player = new Player*[Player::MAX_PLAYER];


	m_player[0] = new Player(L"CModel\\Player.cmo", Vec3(-5.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\PlayerB.cmo", Vec3(5.0f, 0.0f, 0.0f), 0, RIGHT);

	m_enemy = new Enemy(L"CModel\\PlayerB.cmo");
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
PlayScene::~PlayScene()
{
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		delete m_player;
	}
	delete[] m_player;

	delete m_enemy;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void PlayScene::Update()
{
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->Update();
	}

	m_enemy->Update();

	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		if (Collision(m_enemy, m_player[i]->GetGravity()))
		{
			ShunLib::Vec3 vec = m_enemy->Pos();
			m_player[i]->GetGravity()->Attract(&vec);
			m_enemy->Pos(vec);
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
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->DrawGravity(m_view, m_proj);
	}

	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->Draw(m_view, m_proj);
	}

	m_enemy->Draw(m_view, m_proj);

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

