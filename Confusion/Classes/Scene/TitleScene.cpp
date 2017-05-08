//************************************************/
//* @file  :TitleScene.cpp
//* @brief :タイトル画面のソース
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#include "TitleScene.h"
#include "../GameMain.h"

TitleScene::TitleScene()
{
	using namespace ShunLib;
	m_stage = new Stage();

	m_view = Matrix::CreateLookAt(Vec3(0.0f, 30.0f, 40.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 200.0f);

	m_logo = new Texture(L"Images\\Logo.png");

	m_pad = GamePadManager::GetInstance();

}

TitleScene::~TitleScene()
{
	delete m_stage;
	delete m_logo;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void TitleScene::Update()
{
	bool isPush = false;

	isPush = m_pad->Get(0).IsAPressed();
	if (isPush)
	{
		m_nextScene = Scene::PLAY;
	}
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void TitleScene::Render()
{
	m_stage->Draw(m_view,m_proj);

	m_logo->Draw(0.0f, 0.0f);

	//m_testEffect->Draw(m_view, m_proj, ShunLib::Vec3::Zero, ShunLib::Vec3(1.0f,1.0f,1.0f)* 2.0f , 0.2f);


	//static int a = 0;
	//a++;

	//static float b = 0.0f;

	//if (a > 20)
	//{
	//	m_testEffect->ResetDraw(ShunLib::Vec3(b , 0.0f, 0.0f));
	//	a = 0;
	//	b++;
	//	if (b > 20.0f)
	//	{
	//		b = 0.0f;
	//	}
	//}
}
