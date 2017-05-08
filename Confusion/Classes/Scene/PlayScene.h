//************************************************/
//* @file  :PlayScene.h
//* @brief :プレイ画面のヘッダー
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"

#include <vector>
#include "../Wrapper/Matrix/Matrix.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Stage/Stage.h"

#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include "../Wrapper/Effekseer/Effect.h"

class PlayScene:public Scene
{
public:
	//ステージの横幅
	static const float STAGE_TOP;
	static const float STAGE_BOTTOM;
	static const float STAGE_RIGHT;
	static const float STAGE_LEFT;

private:
	ShunLib::Matrix m_view;	//ビュー行列
	ShunLib::Matrix m_proj;	//プロジェクション行列

	//ステージ
	Stage* m_stage;

	//プレイヤー＆敵
	Player** m_player;
	std::vector<Enemy*> m_enemy;

	//エフェクト
	ShunLib::Effect* m_summonEffect;
	ShunLib::Effect* m_blastEffect;

	//プレイ開始でtrue
	bool m_isStarted;

	//クリアorゲームオーバーでtrue
	bool m_isEnded;

public:
	PlayScene();
	~PlayScene();

	//更新＆描画
	void Update()override;
	void Render()override;


private:
	//プレイ開始前の処理
	void PlayAgo();

	//プレイ中の処理
	void PlayMain();

	//プレイクリアの処理
	void PlayClear();

	//プレイゲームオーバーの処理
	void PlayGameOver();

	//当たり判定総合
	void Collision();

	//当たり判定それぞれ
	bool Collision(Object* obj, Object* obj2);
	bool Collision(Object* obj, Gravity* gra);

	//挟まれているかの判定
	bool IsSandwiched(bool isHitGravity[],Enemy* enemy);

	//敵を生成
	void CreateEnemy();

	//クリア判定
	bool IsCleared();
	bool IsGameOver();

};

