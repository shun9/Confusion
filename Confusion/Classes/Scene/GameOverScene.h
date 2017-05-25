//************************************************/
//* @file  :GameOverScene.h
//* @brief :ゲームオーバー画面のクラス
//* @date  :2017/05/09
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"
#include "../Wrapper/Texture/Texture.h"

class GamePadManager;

class GameOverScene:public Scene
{
private:
	GamePadManager* m_gamePad;
	ShunLib::Texture* m_playerDownGrp;
	ShunLib::Texture* m_gameOverGrp;

public:
	GameOverScene();
	~GameOverScene();
	void Update()override;
	void Render()override;
};