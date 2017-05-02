//************************************************/
//* @file  :Player.h
//* @brief :プレイヤーのヘッダー
//* @date  :2017/04/28
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
private:
	//速度倍率
	static const float SPD_MAGNIFICATION;

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

	//ヒットポイント
	int m_hp;
	
	//無敵時間
	int m_invincibleTime;

	/*--公開関数--*/
public:
	Player(const wchar_t* model,
		   ShunLib::Vec3 pos,
		   int gamePadNum,
		   DIRECTION stick);
	~Player();

	//更新処理
	void Update()override;

	//重力の描画
	void DrawGravity(const ShunLib::Matrix& view, const ShunLib::Matrix& proj)
	{	m_gravity->Draw(view, proj);	}

	//重力の情報を返す
	Gravity* GetGravity() { return m_gravity; }
	
	//ダメージを受ける
	void TakeDamage(int damage) {m_hp -= damage;}

	//ＨＰ
	int Hp() { return m_hp; }

	//無敵時間
	int InvincibleTime() { return m_invincibleTime; }
	void InvincibleTime(int time) { m_invincibleTime = time; }

	//ステージ外に出ないようにする
	void Clamp(float top,float bottom,float right,float left);

	/*--非公開関数--*/
private:
	//移動速度の更新
	void UpdateSpd();

	//重力関連の更新
	void UpdateGravity();

	//重力の拡大率の更新
	void UpdateGravityScale();
};
