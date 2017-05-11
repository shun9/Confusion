//************************************************/
//* @file  :PlayScene.h
//* @brief :�v���C��ʂ̃w�b�_�[
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"
#include <memory>
#include <vector>
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include "../Wrapper/Effekseer/Effect.h"
#include "../Wrapper/Matrix/Matrix.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Stage/Stage.h"
#include "../Enemy/SummonMagic.h"
#include "../Object/HPGauge.h"

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

	//�c��̗�
	int m_stageLife;
	HPGauge* m_hpGauge;

	//�v���C���[���G
	Player** m_player;
	std::vector<std::shared_ptr<Enemy>> m_enemy;

	//�G�������@�w
	SummonMagic** m_magic;
	int m_maxMagic;

	//�G�t�F�N�g
	ShunLib::Effect* m_blastEffect;
	ShunLib::Effect* m_clearEffect;

	//�v���C�J�n��true
	bool m_isStarted;

	//�N���Aor�Q�[���I�[�o�[��true
	bool m_isEnded;

public:
	PlayScene();
	~PlayScene();

	//�X�V���`��
	void Update()override;
	void Render()override;


private:
	//�v���C�J�n�O�̏���
	void PlayAgo();

	//�v���C���̏���
	void PlayMain();

	//�v���C�N���A�̏���
	//�I��������true
	bool PlayClear();

	//�v���C�Q�[���I�[�o�[�̏���
	//�I��������true
	bool PlayGameOver();

	//�����蔻�葍��
	void Collision();

	//�����蔻�肻�ꂼ��
	bool Collision(Object* obj, Object* obj2);
	bool Collision(Object* obj, Gravity* gra);

	//���܂�Ă��邩�̔���
	bool IsSandwiched(bool isHitGravity[],Enemy* enemy);

	//�G�𐶐�
	void CreateEnemy();

	//�N���A����
	bool IsCleared();
	bool IsGameOver();

};

