//************************************************/
//* @file  :Gravity.cpp
//* @brief :プレイヤーが発する重力のクラス
//* @date  :2017/04/23
//* @author:S.Katou
//************************************************/
#include "Gravity.h"

using namespace ShunLib;
const float Gravity::POWER = 0.07f;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//｜引数  :画像のパス(wchar_t)
//｜引数  :初期位置(Vec3)
//＋ーーーーーーーーーーーーーー＋
Gravity::Gravity(const wchar_t* texture, const Vec3 & pos)
	: m_texture(new Texture(texture)) //delete -> ~Gravity
	, m_pos(pos)
	, m_radius(1.0f)
	, m_angle(360.0f)
{

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Gravity::~Gravity()
{
	delete m_texture;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Gravity::Update()
{
	//時計回りで回転させる
	m_angle -= 2.0f;

	if (m_angle <= 0.0f)
	{
		m_angle = 360.0f;
	}
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画
//｜引数  :ビュー行列(Matrix)
//｜引数  :射影行列(Matrix)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Gravity::Draw(Matrix view, Matrix proj)
{
	Matrix world;
	world = Matrix::CreateScale(m_radius*2)
		  * Matrix::CreateRotationY(m_angle)
    	  * Matrix::CreateTranslation(m_pos);

	m_texture->Draw(world, view, proj);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :対象を引き寄せる
//｜引数  :対象の位置(Vec3*)書き換える
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Gravity::Attract(ShunLib::Vec3* objPos)
{
	using namespace ShunLib;

	//重力が発生していなければ終了
	if (m_radius <= 0.0f)
	{
		return;
	}

	float x = objPos->m_x - m_pos.m_x;
	float z = objPos->m_z - m_pos.m_z;

	Vec3 vec = { x, 0.0f, z };
	vec.Normalize();
	objPos->m_x -= vec.m_x*POWER;
	objPos->m_z -= vec.m_z*POWER;
}
