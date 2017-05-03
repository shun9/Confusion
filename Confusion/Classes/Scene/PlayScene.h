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

public:
	PlayScene();
	~PlayScene();

	void Update()override;
	void Render()override;

private:
	//当たり判定総合
	void Collision();

	//当たり判定それぞれ
	bool Collision(Object* obj, Object* obj2);
	bool Collision(Object* obj, Gravity* gra);

	//挟まれているかの判定
	bool IsSandwiched(bool isHitGravity[],Enemy* enemy);

	//敵を生成
	void CreateEnemy();
};

