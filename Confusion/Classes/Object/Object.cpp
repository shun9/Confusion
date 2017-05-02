//************************************************/
//* @file  :Object.cpp
//* @brief :オブジェクトの基底クラス
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#include "Object.h"
#include "../Conversion/Conversion.h"

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//｜引数  :画像のパス(wchar_t*)
//｜引数  :初期座標	 (ShunLib::Vec3)
//＋ーーーーーーーーーーーーーー＋
Object::Object(const wchar_t* model, ShunLib::Vec3 pos, ShunLib::Vec3 spd)
	: m_angle(0.0f)
{
	using namespace ShunLib;

	//delete -> ~Object
	m_model = new Model(model);
	m_pos   = new Vec3(pos);
	m_spd   = new Vec3(spd);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Object::~Object()
{
	delete m_model;
	delete m_pos;
	delete m_spd;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画
//｜引数  :ワールド行列		   (ShunLib::Matrix)
//｜引数  :ビュー行列		   (ShunLib::Matrix)
//｜引数  :プロジェクション行列(ShunLib::Matrix)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Object::Draw(const ShunLib::Matrix& view, const ShunLib::Matrix& proj)
{
	using namespace ShunLib;

	//向いている方向を計算する
	CalculateDirection();

	Matrix world = Matrix::CreateRotationY(m_angle) * Matrix::CreateTranslation(*m_pos);
	m_model->Draw(world, view, proj);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :向いている方向を計算する
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Object::CalculateDirection()
{
	//動いていなければ計算しない
	if (m_spd->m_x == 0.0f&&m_spd->m_y==0.0f&&m_spd->m_z==0.0f)
	{
		return;
	}

	m_spd->Normalize();

	float rot = ShunLib::ToAngle(std::atan2(m_spd->m_z, m_spd->m_x)) - 90.0f;

	m_angle = rot;
}
