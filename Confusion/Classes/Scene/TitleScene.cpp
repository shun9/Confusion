//************************************************/
//* @file  :TitleScene.cpp
//* @brief :�^�C�g����ʂ̃\�[�X
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
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 100.0f);

	m_logo = new Texture(L"Images\\Logo.png");

	m_pad = GamePadManager::GetInstance();
}

TitleScene::~TitleScene()
{
	delete m_stage;
	delete m_logo;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void TitleScene::Update()
{
	bool isPush = false;

	isPush = m_pad->Get(0).IsAPressed();
	if (isPush)
	{
		m_nextScene = Scene::PLAY;
	}
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void TitleScene::Render()
{
	m_stage->Draw(m_view,m_proj);

	m_logo->Draw(0.0f, 0.0f);
}
