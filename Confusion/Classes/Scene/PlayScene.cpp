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
	m_view = Matrix::CreateLookAt(Vec3(0.0f, 15.0f, 20.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 100.0f);

	m_player = new Player*[Player::MAX_PLAYER];


	m_player[0] = new Player(L"CModel\\robot.cmo", Vec3(0.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\robot.cmo", Vec3(0.0f, 0.0f, 0.0f), 0, RIGHT);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
PlayScene::~PlayScene()
{
	delete[] m_player;
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
}
