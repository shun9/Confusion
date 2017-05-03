//************************************************/
//* @file  :GameMain.cpp
//* @brief :�Q�[���̃��C���N���X�@�L���p
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#include "GameMain.h"
#include "Wrapper\Vec3\Vec3.h"
#include "Scene\PlayScene.h"
#include "Scene\TitleScene.h"

using namespace ShunLib;


int GameMain::screenW;
int GameMain::screenH;


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :����������
//�b����  :�X�N���[���̉���(int)
//�b����  :�X�N���[���̏c��(int)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void GameMain::Initialize(int screenW, int screenH)
{
	this->screenW = screenW;
	this->screenH = screenH;

	m_view = Matrix::CreateLookAt(Vec3(0.0f,0.0f,5.0f),Vec3::Zero,Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(screenW / screenH), 1.0f, 100.0f);

	//�ŏ��̃V�[��
	//m_scene = new PlayScene;
	m_scene = new TitleScene;
	m_currentScene = Scene::TITLE;
	m_nextScene = m_currentScene;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void GameMain::Update()
{
	//���̃V�[�����擾
	m_nextScene = Scene::NextScene();

	//���̃V�[���ƌ��݂̃V�[�����Ⴄ�ꍇ
	if (m_nextScene != m_currentScene)
	{
		m_currentScene = m_nextScene;

		delete m_scene;
		switch (m_nextScene)
		{
		case Scene::TITLE:
			m_scene = new TitleScene;
			break;

		case Scene::PLAY:
			m_scene = new PlayScene;
			break;

		default:
			break;
		}
	}

	//�V�[���X�V
	m_scene->Update();
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void GameMain::Render()
{
	//�V�[���`��
	m_scene->Render();
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�I������
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void GameMain::Finalize()
{
	if (m_scene != nullptr)
	{
		delete m_scene;
		m_scene = nullptr;
	}
}
