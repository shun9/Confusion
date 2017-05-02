//************************************************/
//* @file  :GameMain.cpp
//* @brief :ゲームのメインクラス　メソッド記入用
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#include "GameMain.h"
#include "Wrapper\Vec3\Vec3.h"
#include "Scene\PlayScene.h"

using namespace ShunLib;


int GameMain::screenW;
int GameMain::screenH;


//＋ーーーーーーーーーーーーーー＋
//｜機能  :初期化処理
//｜引数  :スクリーンの横幅(int)
//｜引数  :スクリーンの縦幅(int)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void GameMain::Initialize(int screenW, int screenH)
{
	this->screenW = screenW;
	this->screenH = screenH;

	m_view = Matrix::CreateLookAt(Vec3(0.0f,0.0f,5.0f),Vec3::Zero,Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(screenW / screenH), 1.0f, 100.0f);

	m_scene = new PlayScene;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void GameMain::Update()
{
	//シーン切り替え

	//シーン更新
	m_scene->Update();
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void GameMain::Render()
{
	//シーン描画
	m_scene->Render();
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :終了処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void GameMain::Finalize()
{
	if (m_scene != nullptr)
	{
		delete m_scene;
		m_scene = nullptr;
	}
}
