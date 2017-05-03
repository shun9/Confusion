//************************************************/
//* @file  :GameMain.cpp
//* @brief :ゲームのメインクラス　記入用
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#include "GameMain.h"
#include "Wrapper\Vec3\Vec3.h"
#include "Scene\PlayScene.h"
#include "Scene\TitleScene.h"

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

	//最初のシーン
	//m_scene = new PlayScene;
	m_scene = new TitleScene;
	m_currentScene = Scene::TITLE;
	m_nextScene = m_currentScene;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void GameMain::Update()
{
	//次のシーンを取得
	m_nextScene = Scene::NextScene();

	//次のシーンと現在のシーンが違う場合
	if (m_nextScene != m_currentScene)
	{
		m_currentScene = m_nextScene;

		delete m_scene;
		switch (m_nextScene)
		{
		case Scene::TITLE:
			m_scene = new TitleScene;
			break;

		case Scene::PLAY:
			m_scene = new PlayScene;
			break;

		default:
			break;
		}
	}

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
