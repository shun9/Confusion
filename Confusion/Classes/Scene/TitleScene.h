//************************************************/
//* @file  :TitleScene.h
//* @brief :タイトル画面のヘッダー
//* @date  :2017/05/23
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"
#include "../Stage/Stage.h"
#include "../Wrapper/Texture/Texture.h"
#include "../Wrapper/GamePad/GamePadManager.h"
#include "../Wrapper/Effekseer/Effect.h"
#include "../Timer/Timer.h"

class TitleScene : public Scene
{
private:
	//背景用ステージ
	Stage* m_stage;

	//タイトルロゴ
	ShunLib::Texture* m_logo;

	//スタートボタンとエンドボタン
	ShunLib::Texture* m_startButton;
	ShunLib::Texture* m_endButton;

	//ビュー行列 & プロジェクション行列
	ShunLib::Matrix m_view;
	ShunLib::Matrix m_proj;

	//矢印
	ShunLib::Texture* m_arrow;

	//ゲームパッド
	GamePadManager* m_pad;

	//背景
	ShunLib::Texture* m_backGround;

	//選んでいるシーンの選択肢
	int m_selectScene;

	//選択肢の移動のトリガー
	bool m_isChangeSelect;

	//始まった直後の入力を受け付けない時間
	ShunLib::Timer* m_waitingTimer;
public:
	TitleScene();
	~TitleScene();

	void Update()override;
	void Render()override;

private:
	void DrawOption();
};