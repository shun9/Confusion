//************************************************/
//* @file  :ClearScene.cpp
//* @brief :ゲームクリア画面のクラス
//* @date  :2017/05/24
//* @author:S.Katou
//************************************************/
#include "ClearScene.h"
#include "../Sound/ADX2Le.h"
#include "../Sound/ClearScene.h"
#include "../Wrapper/ConstantNumber/MacroConstants.h"

ClearScene::ClearScene()
{
	m_gamePad = GamePadManager::GetInstance();
	m_playerRejoiceGrp = new ShunLib::Texture(L"Images\\GameClear.png");
	m_clearGrp = new ShunLib::Texture(L"Images\\Clear.png");
	ADX2Le::LoadAcb("Sounds\\ClearScene.acb", "Sounds\\ClearScene.awb");
	ADX2Le::Play(CRI_CLEARSCENE_CLEAR);
}

ClearScene::~ClearScene()
{
	DELETE_POINTER(m_playerRejoiceGrp);
	DELETE_POINTER(m_clearGrp);
}

void ClearScene::Update()
{
	auto state = m_gamePad->Get(0);

	if (state.IsAPressed())
	{
		m_nextScene = TITLE;
	}

}

void ClearScene::Render()
{
	m_playerRejoiceGrp->Draw(-120.0f, 50.0f);
	m_clearGrp->Draw(340.0f, 0.0f,0.9f);
}
