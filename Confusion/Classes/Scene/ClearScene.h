//************************************************/
//* @file  :ClearScene.h
//* @brief :ゲームクリア画面のクラス
//* @date  :2017/05/24
//* @author:S.Katou
//************************************************/
#pragma once

#include "Scene.h"
#include "../Wrapper/Texture/Texture.h"
#include "../Wrapper/GamePad/GamePadManager.h"

class ClearScene :public Scene
{
private:
	GamePadManager* m_gamePad;
	ShunLib::Texture* m_playerRejoiceGrp;
	ShunLib::Texture* m_clearGrp;

public:
	ClearScene();
	~ClearScene();

	void Update()override;
	void Render()override;
};