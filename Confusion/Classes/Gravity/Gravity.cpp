//************************************************/
//* @file  :Gravity.cpp
//* @brief :プレイヤーが発する重力のクラス
//* @date  :2017/04/23
//* @author:S.Katou
//************************************************/
#include "Gravity.h"

using namespace ShunLib;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//｜引数  :画像のパス(wchar_t)
//｜引数  :初期位置(Vec3)
//＋ーーーーーーーーーーーーーー＋
Gravity::Gravity(const wchar_t* texture, const Vec3 & pos)
	: m_texture(new Texture(texture)) //delete -> ~Gravity
	, m_pos(pos)
	, m_scale(1.0f)
	, m_angle(360.0f)
{

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Gravity::~Gravity()
{
	//new -> Gravity
	delete m_texture;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Gravity::Update()
{
	//時計回り
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
	world = Matrix::CreateScale(m_scale)
		  * Matrix::CreateRotationY(m_angle)
    	  * Matrix::CreateTranslation(m_pos);

	m_texture->Draw(world, view, proj);
}
