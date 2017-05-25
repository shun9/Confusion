//************************************************/
//* @file  :GameMain.h
//* @brief :ゲームのメインクラス　記入用
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene\Scene.h"
#include "Wrapper\Matrix\Matrix.h"
#include "Wrapper\Texture\Texture.h"

class GameMain
{
public:
	static int screenW;
	static int screenH;

private:
	//シーン
	Scene* m_scene;

	//現在のシーン
	int m_currentScene;

	//次のシーン
	int m_nextScene;

	//ビュー行列
	ShunLib::Matrix m_view;	

	//プロジェクション行列
	ShunLib::Matrix m_proj;	

	bool m_isEnded;

public:
	//初期化処理
	void Initialize(int screenW,int screenH);
	
	//更新処理
	void Update();

	//描画処理
	void Render();
	
	//終了処理
	void Finalize();

	//終了したかどうか
	bool IsEnded();

	//コンストラクタ＆デストラクタ
	GameMain() {};
	~GameMain() {};
};