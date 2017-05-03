//************************************************/
//* @file  :TitleScene.h
//* @brief :タイトル画面のヘッダー
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"
#include "../Stage/Stage.h"
#include "../Wrapper/Texture/Texture.h"
#include "../Wrapper/GamePad/GamePadManager.h"

class TitleScene : public Scene
{
private:
	//背景用ステージ
	Stage* m_stage;

	//タイトルロゴ
	ShunLib::Texture* m_logo;

	ShunLib::Matrix m_view;	//ビュー行列
	ShunLib::Matrix m_proj;	//プロジェクション行列

	//ゲームパッド
	GamePadManager* m_pad;

public:
	TitleScene();
	~TitleScene();

	void Update()override;
	void Render()override;

};