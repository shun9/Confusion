//************************************************/
//* @file  :PlayScene.h
//* @brief :�v���C��ʂ̃w�b�_�[
//* @date  :2017/05/17
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
#include "../Enemy/BossMagic.h"
#include "../Timer/Timer.h"

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
	int m_stageHP;
	HPGauge* m_hpGauge;

	//�{�X�̃��C�t�Q�[�W
	HPGauge* m_bossGauge;

	//�v���C���[���G
	Player** m_player;
	std::vector<std::shared_ptr<Enemy>> m_enemy;

	//�G�������@�w
	std::vector<std::shared_ptr<SummonMagic>>m_magic;
	std::unique_ptr<BossMagic>m_boss;

	//�G�t�F�N�g
	ShunLib::Effect* m_blastEffect;
	ShunLib::Effect* m_endEffect;

	//�v���C�J�n��true
	bool m_isStarted;

	//�N���Aor�Q�[���I�[�o�[��true
	bool m_isEnded;

	//���@�w�����p
	ShunLib::Timer* m_createMagicTimer;

public:
	PlayScene();
	~PlayScene();

	//�X�V���`��
	void Update()override;
	void Render()override;


private:
	//�G�֘A�̍X�V
	void UpdateEnemy();

	//���@�w�֘A�̕`��
	void UpdateMagic();

	//�X�e�[�W�̕`��
	void DrawStage();

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

	//���@�w����
	void CreateMagic();

	//�S�Ă̖��@�w���폜
	void DeleteAllMagic();

	//�N���A����
	bool IsCleared();
	bool IsGameOver();
};

