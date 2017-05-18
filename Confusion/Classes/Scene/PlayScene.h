//************************************************/
//* @file  :PlayScene.h
//* @brief :プレイ画面のヘッダー
//* @date  :2017/05/17
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"
#include <memory>
#include <vector>
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include "../Wrapper/Effekseer/Effect.h"
#include "../Wrapper/Matrix/Matrix.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Stage/Stage.h"
#include "../Enemy/SummonMagic.h"
#include "../Object/HPGauge.h"
#include "../Enemy/BossMagic.h"
#include "../Timer/Timer.h"

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

	//残り体力
	int m_stageHP;
	HPGauge* m_hpGauge;

	//ボスのライフゲージ
	HPGauge* m_bossGauge;

	//プレイヤー＆敵
	Player** m_player;
	std::vector<std::shared_ptr<Enemy>> m_enemy;

	//敵召喚魔法陣
	std::vector<std::shared_ptr<SummonMagic>>m_magic;
	std::unique_ptr<BossMagic>m_boss;

	//エフェクト
	ShunLib::Effect* m_blastEffect;
	ShunLib::Effect* m_endEffect;

	//プレイ開始でtrue
	bool m_isStarted;

	//クリアorゲームオーバーでtrue
	bool m_isEnded;

	//魔法陣召喚用
	ShunLib::Timer* m_createMagicTimer;

public:
	PlayScene();
	~PlayScene();

	//更新＆描画
	void Update()override;
	void Render()override;


private:
	//敵関連の更新
	void UpdateEnemy();

	//魔法陣関連の描画
	void UpdateMagic();

	//ステージの描画
	void DrawStage();

	//プレイ開始前の処理
	void PlayAgo();

	//プレイ中の処理
	void PlayMain();

	//プレイクリアの処理
	//終了したらtrue
	bool PlayClear();

	//プレイゲームオーバーの処理
	//終了したらtrue
	bool PlayGameOver();

	//当たり判定総合
	void Collision();

	//当たり判定それぞれ
	bool Collision(Object* obj, Object* obj2);
	bool Collision(Object* obj, Gravity* gra);

	//挟まれているかの判定
	bool IsSandwiched(bool isHitGravity[],Enemy* enemy);

	//魔法陣生成
	void CreateMagic();

	//全ての魔法陣を削除
	void DeleteAllMagic();

	//クリア判定
	bool IsCleared();
	bool IsGameOver();
};

