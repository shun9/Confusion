//************************************************/
//* @file  :GameMain.cpp
//* @brief :ゲームのメインクラス　記入用
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#include "GameMain.h"
#include <ctime>
#include "Sound\ADX2Le.h"
#include "Wrapper\Vec3\Vec3.h"
#include "Scene\PlayScene.h"
#include "Scene\TitleScene.h"
#include "Scene\GameOverScene.h"
#include "Scene\ClearScene.h"

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

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	m_view = Matrix::CreateLookAt(Vec3(0.0f,0.0f,5.0f),Vec3::Zero,Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(screenW / screenH), 1.0f, 100.0f);

	ADX2Le::Initialize("Sounds\\Confusion.acf");


	m_isEnded = false;

	//最初のシーン
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

	//次のシーンと現在のシーンが違う場合シーンを変更する
	if (m_nextScene != m_currentScene)
	{
		m_currentScene = m_nextScene;

		if (m_scene != nullptr){
			delete m_scene;
			m_scene = nullptr;
		}

		switch (m_nextScene)
		{
		case Scene::TITLE:
			m_scene = new TitleScene;
			break;

		case Scene::PLAY:
			m_scene = new PlayScene;
			break;

		case Scene::CLEAR:
			m_scene = new ClearScene;
			break;

		case Scene::OVER:
			m_scene = new GameOverScene;
			break;

		case Scene::EXIT:
			m_isEnded = true;
			return;

		default:
			break;
		}
	}

	//シーン更新
	if (m_scene != nullptr)
	{
		m_scene->Update();
	}

	ADX2Le::Update();
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void GameMain::Render()
{
	//シーン描画
	if (m_scene != nullptr)
	{
		m_scene->Render();
	}
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


	ADX2Le::Finalize();
}

bool GameMain::IsEnded()
{
	return m_isEnded;
}
