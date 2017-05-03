//************************************************/
//* @file  :TitleScene.h
//* @brief :�^�C�g����ʂ̃w�b�_�[
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"
#include "../Stage/Stage.h"
#include "../Wrapper/Texture/Texture.h"
#include "../Wrapper/GamePad/GamePadManager.h"

class TitleScene : public Scene
{
private:
	//�w�i�p�X�e�[�W
	Stage* m_stage;

	//�^�C�g�����S
	ShunLib::Texture* m_logo;

	ShunLib::Matrix m_view;	//�r���[�s��
	ShunLib::Matrix m_proj;	//�v���W�F�N�V�����s��

	//�Q�[���p�b�h
	GamePadManager* m_pad;

public:
	TitleScene();
	~TitleScene();

	void Update()override;
	void Render()override;

};