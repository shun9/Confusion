//************************************************/
//* @file  :GameMain.h
//* @brief :ゲームのメインクラス　記入用
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene\Scene.h"
#include "Wrapper\Matrix\Matrix.h"

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

	ShunLib::Matrix m_view;	//ビュー行列
	ShunLib::Matrix m_proj;	//プロジェクション行列

public:
	//初期化処理
	void Initialize(int screenW,int screenH);
	
	//更新処理
	void Update();

	//描画処理
	void Render();
	
	//終了処理
	void Finalize();


	//コンストラクタ＆デストラクタ
	GameMain() {};
	~GameMain() {};
};