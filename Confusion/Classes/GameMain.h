//************************************************/
//* @file  :GameMain.h
//* @brief :�Q�[���̃��C���N���X�@���\�b�h�L���p
//* @date  :2017/04/18
//* @author:S.Katou
//************************************************/
#pragma once
#include "Wrapper\Model\Model.h"
#include "Wrapper\Matrix\Matrix.h"
#include "Wrapper\Texture\Texture.h"
#include "Wrapper\Texture\Texture.h"
#include "Wrapper\Model\Model.h"


class GameMain
{
private:
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