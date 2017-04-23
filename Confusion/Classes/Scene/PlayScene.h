//************************************************/
//* @file  :PlayScene.h
//* @brief :�v���C��ʂ̃w�b�_�[
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"
#include "../Wrapper/Matrix/Matrix.h"
#include "../Player/Player.h"
#include "../Wrapper/Texture/Texture.h"

class PlayScene:public Scene
{
private:
	ShunLib::Matrix m_view;	//�r���[�s��
	ShunLib::Matrix m_proj;	//�v���W�F�N�V�����s��

	Player** m_player;

public:
	PlayScene();
	~PlayScene();

	void Update()override;
	void Render()override;
};