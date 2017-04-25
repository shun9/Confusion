//************************************************/
//* @file  :PlayScene.cpp
//* @brief :�v���C��ʂ̃\�[�X
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#include "PlayScene.h"
#include "../Wrapper/Vec3/Vec3.h"
#include "../GameMain.h"

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
PlayScene::PlayScene()
{
	using namespace ShunLib;
	m_view = Matrix::CreateLookAt(Vec3(0.0f, 15.0f, 20.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 100.0f);

	m_player = new Player*[Player::MAX_PLAYER];


	m_player[0] = new Player(L"CModel\\Player.cmo", Vec3(0.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\robot.cmo", Vec3(0.0f, 0.0f, 0.0f), 0, RIGHT);

	m_enemy = new Enemy(L"CModel\\robot.cmo");
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
PlayScene::~PlayScene()
{
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		delete m_player;
	}
	delete[] m_player;

	delete m_enemy;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::Update()
{
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->Update();
	}

	m_enemy->Update();
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::Render()
{
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->DrawGravity(m_view, m_proj);
	}

	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->Draw(m_view, m_proj);
	}

	m_enemy->Draw(m_view, m_proj);

}
