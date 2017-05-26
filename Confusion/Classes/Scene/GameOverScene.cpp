//************************************************/
//* @file  :GameOverScene.cpp
//* @brief :ゲームオーバー画面のクラス
//* @date  :2017/05/23
//* @author:S.Katou
//************************************************/
#include "GameOverScene.h"
#include "../Wrapper/GamePad/GamePadManager.h"
#include "../Sound/ADX2Le.h"
#include "../Sound/GameOverScene.h"
#include "../Wrapper/ConstantNumber/MacroConstants.h"

GameOverScene::GameOverScene()
{
	m_gamePad = GamePadManager::GetInstance();
	m_playerDownGrp = new ShunLib::Texture(L"Images\\GameOver.png");
	m_gameOverGrp = new ShunLib::Texture(L"Images\\Over.png");
	ADX2Le::LoadAcb("Sounds\\GameOverScene.acb", "Sounds\\GameOverScene.awb");
	ADX2Le::Play(CRI_GAMEOVERSCENE_GAMEOVER,0.3f);
}

GameOverScene::~GameOverScene()
{
	DELETE_POINTER(m_playerDownGrp);
}

void GameOverScene::Update()
{
	auto state = m_gamePad->Get(0);

	if (state.IsAPressed())
	{
		m_nextScene = TITLE;
	}
}

void GameOverScene::Render()
{
	m_playerDownGrp->Draw(-110.0f, 0.0f);
	m_gameOverGrp->Draw(340.0f, 40.0f,0.9f);
}

