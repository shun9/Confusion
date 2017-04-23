//************************************************/
//* @file  :GameMain.h
//* @brief :�Q�[���̃��C���N���X�@���\�b�h�L���p
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene\Scene.h"
#include "Wrapper\Matrix\Matrix.h"

class GameMain
{
public:
	static int screenW;
	static int screenH;

private:
	Scene* m_scene;

	ShunLib::Matrix m_view;	//�r���[�s��
	ShunLib::Matrix m_proj;	//�v���W�F�N�V�����s��

public:
	//����������
	void Initialize(int screenW,int screenH);
	
	//�X�V����
	void Update();

	//�`�揈��
	void Render();
	
	//�I������
	void Finalize();


	//�R���X�g���N�^���f�X�g���N�^
	GameMain() {};
	~GameMain() {};
};