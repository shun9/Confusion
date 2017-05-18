//************************************************/
//* @file  :Stage.cpp
//* @brief :ステージ描画用のクラス
//* @date  :2017/05/14
//* @author:S.Katou
//************************************************/
#include "Stage.h"

#include "../Scene/PlayScene.h"

Stage::Stage()
{
	using namespace ShunLib;
	//m_ground = new Texture(L"Images\\glass.jpg");
	m_ground = new Model(L"CModel\\Glass.cmo");
	m_tree = new Model(L"CModel\\tree.cmo");
}

Stage::~Stage()
{
	delete m_ground;
	delete m_tree;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画
//｜引数  :ビュー行列		   (ShunLib::Matrix)
//｜引数  :プロジェクション行列(ShunLib::Matrix)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Stage::Draw(const ShunLib::Matrix& world,
				 const ShunLib::Matrix& view,
				 const ShunLib::Matrix& proj)
{
	using namespace ShunLib;

	//地面描画
	m_ground->Draw(world, view, proj);

	//木描画
	for (int i = 0; i < 20; i++)
	{
		Matrix worldLeft = Matrix::CreateTranslation(Vec3(PlayScene::STAGE_LEFT-3.0f, 0.0f, 25.0f - 4 * i));
		Matrix worldRight = Matrix::CreateTranslation(Vec3(PlayScene::STAGE_RIGHT+3.0f, 0.0f, 25.0f - 4 * i));
		m_tree->Draw(worldLeft, view, proj);
		m_tree->Draw(worldRight, view, proj);
	}
}
