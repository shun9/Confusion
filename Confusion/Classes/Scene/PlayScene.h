//************************************************/
//* @file  :PlayScene.h
//* @brief :�v���C��ʂ̃w�b�_�[
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"

#include <vector>
#include "../Wrapper/Matrix/Matrix.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Stage/Stage.h"

#include <Effekseer.h>
#include <EffekseerRendererDX11.h>

class PlayScene:public Scene
{
public:
	//�X�e�[�W�̉���
	static const float STAGE_TOP;
	static const float STAGE_BOTTOM;
	static const float STAGE_RIGHT;
	static const float STAGE_LEFT;

private:
	ShunLib::Matrix m_view;	//�r���[�s��
	ShunLib::Matrix m_proj;	//�v���W�F�N�V�����s��

	//�X�e�[�W
	Stage* m_stage;

	//�v���C���[���G
	Player** m_player;
	std::vector<Enemy*> m_enemy;

public:
	PlayScene();
	~PlayScene();

	void Update()override;
	void Render()override;

private:
	//�����蔻�葍��
	void Collision();

	//�����蔻�肻�ꂼ��
	bool Collision(Object* obj, Object* obj2);
	bool Collision(Object* obj, Gravity* gra);

	//���܂�Ă��邩�̔���
	bool IsSandwiched(bool isHitGravity[],Enemy* enemy);

	//�G�𐶐�
	void CreateEnemy();
};

