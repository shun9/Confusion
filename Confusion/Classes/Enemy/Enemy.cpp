//************************************************/
//* @file  :Enemy.cpp
//* @brief :敵のソースファイル
//* @date  :2017/04/24
//* @author:S.Katou
//************************************************/
#include "Enemy.h"

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//｜引数  :画像のパス(wchar_t*)
//｜引数  :初期座標	 (ShunLib::Vec3)
//＋ーーーーーーーーーーーーーー＋
Enemy::Enemy(const wchar_t* model, ShunLib::Vec3 pos)
	: Object(model,pos)
{
	m_spd->m_z = 0.0f;

	m_radius = 1.0f;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Enemy::~Enemy()
{
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Enemy::Update()
{
	*m_pos = *m_pos + *m_spd;
}
