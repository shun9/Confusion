//************************************************/
//* @file  :Player.cpp
//* @brief :プレイヤーのソールファイル
//* @date  :2017/04/22
//* @author:S.Katou
//************************************************/
#include "Player.h"
#include "../Wrapper/GamePad/GamePadManager.h"

//プレイヤー最大数
const int Player::MAX_PLAYER = 2;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//｜引数  :画像のパス(wchar_t*)
//｜引数  :初期座標	 (ShunLib::Vec3)
//＋ーーーーーーーーーーーーーー＋
Player::Player(const wchar_t* model, ShunLib::Vec3 pos, int gamePadNum,DIRECTION stick)
	:Object(model, pos)
	,m_gamePadNum(gamePadNum)
	,m_stick(stick)
{
	m_gamePad = GamePadManager::GetInstance();

	//delete -> ~Player
	m_gravity = new Gravity(L"Effect\\gravity.png");
	m_gravity->Scale(0.1f);
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Player::~Player()
{
	//new -> Player
	delete m_gravity;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Player::Update()
{
	//速度更新
	UpdateSpd();

	//移動
	*m_pos = *m_pos + *m_spd;


	//重力位置を移動
	m_gravity->Pos(m_pos->m_x,-1.0f,m_pos->m_z);

	//重力更新
	m_gravity->Update();
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :重力の描画
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Player::DrawGravity(const ShunLib::Matrix & view, const ShunLib::Matrix & proj)
{
	m_gravity->Draw(view, proj);
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :速度の更新
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Player::UpdateSpd()
{
	auto state = m_gamePad->Get(m_gamePadNum);

	//速度を設定
	//Ｚ軸は座標系の関連でマイナスを掛ける
	switch (m_stick)
	{
	case RIGHT://右スティック
		m_spd->m_x = state.thumbSticks.rightX / 10.0f;	
		m_spd->m_z = -(state.thumbSticks.rightY / 10.0f);
		break;

	case LEFT://左スティック
		m_spd->m_x = state.thumbSticks.leftX / 10.0f;
		m_spd->m_z = -(state.thumbSticks.leftY / 10.0f);
		break;

	default://それ以外は左
		m_spd->m_x = state.thumbSticks.leftX / 10.0f;
		m_spd->m_z = -(state.thumbSticks.leftY / 10.0f);
		break;
	}
}

