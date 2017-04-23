//************************************************/
//* @file  :Object.cpp
//* @brief :オブジェクトの基底クラス
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#include "Object.h"

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//｜引数  :画像のパス(wchar_t*)
//｜引数  :初期座標	 (ShunLib::Vec3)
//＋ーーーーーーーーーーーーーー＋
Object::Object(const wchar_t* model, ShunLib::Vec3 pos)
{
	using namespace ShunLib;

	//delete -> ~Object
	m_model = new Model(model);
	m_pos   = new Vec3(pos);
	m_spd   = new Vec3(0.0f, 0.0f, 0.0f);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Object::~Object()
{
	//new -> Object
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

	Matrix world = Matrix::CreateTranslation(*m_pos);
	m_model->Draw(world, view, proj);
}
