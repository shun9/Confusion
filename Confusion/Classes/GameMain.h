//************************************************/
//* @file  :GameMain.h
//* @brief :ゲームのメインクラス　メソッド記入用
//* @date  :2017/04/18
//* @author:S.Katou
//************************************************/
#pragma once
#include "Wrapper\Model\Model.h"
#include "Wrapper\Matrix\Matrix.h"
#include "Wrapper\Texture\Texture.h"
#include "Wrapper\Texture\Texture.h"
#include "Wrapper\Model\Model.h"


class GameMain
{
private:
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