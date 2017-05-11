//************************************************/
//* @file  :GameOverScene.cpp
//* @brief :�Q�[���I�[�o�[��ʂ̃N���X
//* @date  :2017/05/09
//* @author:S.Katou
//************************************************/
#include "GameOverScene.h"
#include "../Wrapper/GamePad/GamePadManager.h"

GameOverScene::GameOverScene()
{
	m_gamePad = GamePadManager::GetInstance();
}

GameOverScene::~GameOverScene()
{

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
}

