//************************************************/
//* @file  :PlayScene.h
//* @brief :プレイ画面のヘッダー
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"
#include "../Wrapper/Matrix/Matrix.h"
#include "../Player/Player.h"
#include "../Wrapper/Texture/Texture.h"

class PlayScene:public Scene
{
private:
	ShunLib::Matrix m_view;	//ビュー行列
	ShunLib::Matrix m_proj;	//プロジェクション行列

	Player** m_player;

public:
	PlayScene();
	~PlayScene();

	void Update()override;
	void Render()override;
};