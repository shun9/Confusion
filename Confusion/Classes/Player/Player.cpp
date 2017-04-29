//************************************************/
//* @file  :Player.cpp
//* @brief :プレイヤーのソースファイル
//* @date  :2017/04/24
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
	: Object(model, pos)
	, m_gamePadNum(gamePadNum)
	, m_stick(stick)
	, m_gravityScale(0.1f)
	, m_hp(10)
	, m_invincibleTime(0)
{
	m_gamePad = GamePadManager::GetInstance();

	m_radius = 0.8f;

	m_gravity = new Gravity(L"Effect\\gravity.png");
	m_gravity->Radius(m_gravityScale);
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Player::~Player()
{
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

	//無敵時間減少
	if (m_invincibleTime > 0)
	{
		m_invincibleTime--;
	}

	//重力関連の更新
	UpdateGravity();
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



//＋ーーーーーーーーーーーーーー＋
//｜機能  :重力関連の更新
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Player::UpdateGravity()
{
	//重力位置を移動
	m_gravity->Pos(m_pos->m_x, -1.0f, m_pos->m_z);


	//重力の拡大率の更新
	UpdateGravityScale();

	//重力を設定
	m_gravity->Radius(m_gravityScale);

	//重力更新
	m_gravity->Update();
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :重力の拡大率更新
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Player::UpdateGravityScale()
{
	auto state = m_gamePad->Get(m_gamePadNum);
	bool isPushed = false;

	//
	switch (m_stick)
	{
	case RIGHT://右スティック
		isPushed = state.IsRightShoulderPressed();
		break;

	case LEFT://左スティック
		isPushed = state.IsLeftShoulderPressed();
		break;

	default://それ以外は左
		isPushed = state.IsLeftShoulderPressed();
		break;
	}

	//押している間広がり続ける
	if (isPushed)
	{
		m_gravityScale += 0.1f;
	}
	else
	{
		m_gravityScale -= 0.1f;
	}

	//縮小しすぎないようにする
	if (m_gravityScale < 0.0f)
	{
		m_gravityScale = 0.0f;
	}
	//拡大しすぎないようにする
	if (m_gravityScale > 10.0f)
	{
		m_gravityScale = 10.0f;
	}
}

