//************************************************/
//* @file  :TitleScene.h
//* @brief :�^�C�g����ʂ̃w�b�_�[
//* @date  :2017/05/23
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"
#include "../Stage/Stage.h"
#include "../Wrapper/Texture/Texture.h"
#include "../Wrapper/GamePad/GamePadManager.h"
#include "../Wrapper/Effekseer/Effect.h"
#include "../Timer/Timer.h"

class TitleScene : public Scene
{
private:
	//�w�i�p�X�e�[�W
	Stage* m_stage;

	//�^�C�g�����S
	ShunLib::Texture* m_logo;

	//�X�^�[�g�{�^���ƃG���h�{�^��
	ShunLib::Texture* m_startButton;
	ShunLib::Texture* m_endButton;

	//�r���[�s�� & �v���W�F�N�V�����s��
	ShunLib::Matrix m_view;
	ShunLib::Matrix m_proj;

	//���
	ShunLib::Texture* m_arrow;

	//�Q�[���p�b�h
	GamePadManager* m_pad;

	//�w�i
	ShunLib::Texture* m_backGround;

	//�I��ł���V�[���̑I����
	int m_selectScene;

	//�I�����̈ړ��̃g���K�[
	bool m_isChangeSelect;

	//�n�܂�������̓��͂��󂯕t���Ȃ�����
	ShunLib::Timer* m_waitingTimer;
public:
	TitleScene();
	~TitleScene();

	void Update()override;
	void Render()override;

private:
	void DrawOption();
};