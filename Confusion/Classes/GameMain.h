//************************************************/
//* @file  :GameMain.h
//* @brief :�Q�[���̃��C���N���X�@�L���p
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene\Scene.h"
#include "Wrapper\Matrix\Matrix.h"
#include "Wrapper\Texture\Texture.h"

class GameMain
{
public:
	static int screenW;
	static int screenH;

private:
	//�V�[��
	Scene* m_scene;

	//���݂̃V�[��
	int m_currentScene;

	//���̃V�[��
	int m_nextScene;

	//�r���[�s��
	ShunLib::Matrix m_view;	

	//�v���W�F�N�V�����s��
	ShunLib::Matrix m_proj;	

	bool m_isEnded;

public:
	//����������
	void Initialize(int screenW,int screenH);
	
	//�X�V����
	void Update();

	//�`�揈��
	void Render();
	
	//�I������
	void Finalize();

	//�I���������ǂ���
	bool IsEnded();

	//�R���X�g���N�^���f�X�g���N�^
	GameMain() {};
	~GameMain() {};
};