//************************************************/
//* @file  :Player.h
//* @brief :プレイヤーのヘッダー
//* @date  :2017/04/22
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Object/Object.h"
#include "../Gravity/Gravity.h"

class GamePadManager;


//定数　方向
enum DIRECTION
{
	TOP,
	BOTTOM,
	RIGHT,
	LEFT,
};


//プレイヤークラス
class Player :public Object
{
	/*--静的変数--*/
public:
	//プレイヤー最大数
	static const int MAX_PLAYER;


	/*--メンバ変数--*/
private:
	//ゲームパッド
	GamePadManager* m_gamePad;
	
	//対応するゲームパッドの番号
	int m_gamePadNum;

	//移動用に対応するスティック（右 or 左）
	DIRECTION m_stick;

	//重力
	Gravity* m_gravity;
	float m_gravityScale;


	/*--メンバ関数--*/
public:
	Player(const wchar_t* model,
		   ShunLib::Vec3 pos,
		   int gamePadNum,
		   DIRECTION stick);
	~Player();

	//更新処理
	void Update()override;

	//重力の描画
	void DrawGravity(const ShunLib::Matrix& view,
				  	 const ShunLib::Matrix& proj);

private:
	//移動速度の更新
	void UpdateSpd();

	//重力関連の更新
	void UpdateGravity();

	//重力の拡大率の更新
	void UpdateGravityScale();
};
