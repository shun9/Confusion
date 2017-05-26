//************************************************/
//* @file  :TitleScene.cpp
//* @brief :タイトル画面のソース
//* @date  :2017/05/19
//* @author:S.Katou
//************************************************/
#include "TitleScene.h"
#include "../GameMain.h"
#include "../Sound/PlayScene.h"
#include "../Sound/TitleScene.h"
#include "../Sound/ADX2Le.h"
#include "../Wrapper/ConstantNumber/MacroConstants.h"

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//＋ーーーーーーーーーーーーーー＋
TitleScene::TitleScene():
	m_selectScene(Scene::PLAY),
	m_isChangeSelect(false)
{
	using namespace ShunLib;
	m_stage = new Stage();

	m_view = Matrix::CreateLookAt(Vec3(0.0f, 8.0f, 20.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(60.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 200.0f);

	m_logo = new Texture(L"Images\\Title.png");
	m_startButton = new Texture(L"Images\\Start.png");
	m_endButton = new Texture(L"Images\\End.png");

	m_pad = GamePadManager::GetInstance();
	m_backGround = new Texture(L"Images\\backGround.png");

	m_arrow = new Texture(L"Images\\magic.png");
	m_waitingTimer = new Timer;
	m_waitingTimer->SetTime(10);

	ADX2Le::LoadAcb("Sounds\\TitleScene.acb", "Sounds\\TitleScene.awb");
	ADX2Le::Play(CRI_TITLESCENE__THE_ROAD_TO_HEAVEN);
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
TitleScene::~TitleScene()
{
	DELETE_POINTER(m_stage);
	DELETE_POINTER(m_logo);
	DELETE_POINTER(m_backGround);
	DELETE_POINTER(m_startButton);
	DELETE_POINTER(m_endButton);
	DELETE_POINTER(m_arrow);
	DELETE_POINTER(m_waitingTimer);
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void TitleScene::Update()
{

	//一定時間経過するまで入力を受け付けない
	if (!(m_waitingTimer->IsEnded()))
	{
		m_waitingTimer->Update();
		return;
	}

	auto padState = m_pad->Get(0);
	bool isPushA = padState.IsAPressed();
	float stickL = padState.thumbSticks.leftY;

	//左スティックが倒されていたら選択肢を変える
	if (std::abs(stickL) > 0.0f)
	{
		if (!m_isChangeSelect)
		{
			switch (m_selectScene)
			{
			case Scene::PLAY:
				m_selectScene = EXIT;
				break;
			case Scene::EXIT:
				m_selectScene = PLAY;
				break;
			default:
				break;
			}

			m_isChangeSelect = true;
		}
	}
	else
	{
		m_isChangeSelect = false;
	}

	//Aボタンが押されたらシーン移動
	if (isPushA)
	{
		m_nextScene = m_selectScene;
	}
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void TitleScene::Render()
{
	using namespace ShunLib;
	//遠景描画
	Matrix backWorld;
	backWorld = Matrix::CreateRotationX(30.0f)
			  * Matrix::CreateScale(Vec3(30.0f, 12.0f, 1.0f))
			  * Matrix::CreateTranslation(Vec3(0.0f, 8.5f, 1.0f));
	m_backGround->Draw(backWorld, m_view, m_proj);

	//近景描画
	Matrix world = Matrix::CreateScale(Vec3(50.0f, 1.0f, 100.0f));
	world = world*Matrix::CreateTranslation(Vec3(0.0f, 0.0f, 0.0f));
	m_stage->Draw(world, m_view, m_proj, true);

	m_logo->Draw(-70.0f, -120.0f,1.2f);
	DrawOption();
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :選択肢の描画処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void TitleScene::DrawOption()
{
	using namespace ShunLib;

	m_startButton->Draw(250.0f, 350.0f);
	m_endButton->Draw(250.0f, 450.0f);


	if (m_selectScene == Scene::PLAY)
	{
		Matrix world = Matrix::CreateScale(0.7f)*Matrix::CreateRotationX(120.0f)*Matrix::CreateTranslation(Vec3(-1.25f, 5.45f, 16.0f));
		m_arrow->Draw(world, m_view, m_proj);

		world = world*Matrix::CreateTranslation(Vec3(2.7f, 0.0f, 0.0f));
		m_arrow->Draw(world, m_view, m_proj);
	}


	if (m_selectScene == Scene::EXIT)
	{
		Matrix world = Matrix::CreateScale(0.7f)*Matrix::CreateRotationX(120.0f)*Matrix::CreateTranslation(Vec3(-1.2f, 4.3f, 16.0f));
		m_arrow->Draw(world, m_view, m_proj);

		world = world*Matrix::CreateTranslation(Vec3(2.55f, 0.0f, 0.0f));
		m_arrow->Draw(world, m_view, m_proj);
	}

}
