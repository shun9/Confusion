//************************************************/
//* @file  :PlayScene.cpp
//* @brief :�v���C��ʂ̃\�[�X
//* @date  :2017/05/01
//* @author:S.Katou
//************************************************/
#include <random>
#include "PlayScene.h"
#include "../Wrapper/Vec3/Vec3.h"
#include "../GameMain.h"
#include "../Conversion/Conversion.h"

//�X�e�[�W�̏㉺���E
const float PlayScene::STAGE_TOP = 20.0f;
const float PlayScene::STAGE_BOTTOM = -60.0f;
const float PlayScene::STAGE_RIGHT = 15.0f;
const float PlayScene::STAGE_LEFT = -15.0f;


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
PlayScene::PlayScene()
{
	using namespace ShunLib;
	m_view = Matrix::CreateLookAt(Vec3(0.0f, 30.0f, 40.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 200.0f);

	//�v���C���[����  delete �[> ~PlayScene
	m_player	= new Player*[Player::MAX_PLAYER];
	m_player[0] = new Player(L"CModel\\Player.cmo", Vec3(-5.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\PlayerB.cmo", Vec3(5.0f, 0.0f, 0.0f), 0, RIGHT);


	//m_summonEffect = new ShunLib::Effect(L"Effect\\MAGICALxSPIRAL\\Magic.efk", 60);
	m_summonEffect = new ShunLib::Effect(L"Effect\\Magic.efk", 60);
	m_blastEffect = new ShunLib::Effect(L"Effect\\Blast.efk", 0,512);

	//�X�e�[�W����
	m_stage = new Stage;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
PlayScene::~PlayScene()
{
	//�v���C���[�폜
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		delete m_player;
	}
	delete[] m_player;

	//�G�폜
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		delete m_enemy[i];
	}

	//�X�e�[�W�폜
	delete m_stage;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::Update()
{
	//�G�o��(��)
	static int t = 0;
	t++;
	if (t > 120)
	{
		CreateEnemy();
		t = 0;
	}


	//�v���C���[�X�V
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->Update();
		m_player[i]->Clamp(STAGE_TOP, STAGE_BOTTOM, STAGE_RIGHT, STAGE_LEFT);
	}

	//�G�X�V
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		m_enemy[i]->Update();
		m_enemy[i]->Dead(STAGE_TOP, STAGE_BOTTOM, STAGE_RIGHT, STAGE_LEFT);
	}

	//�����蔻��
	Collision();

	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		//����ł�����G���폜
		if (m_enemy[i]->IsDead())
		{
			//���j�G�t�F�N�g�ݒ�
			m_blastEffect->SetDraw(m_enemy[i]->Pos()+ ShunLib::Vec3(0.0f, 1.0f, 0.0f));
			//m_blastEffect->SetPos(ShunLib::Vec3(0.0f,1.0f,0.0f));

			//�G�폜
			delete m_enemy[i];
			m_enemy.erase(m_enemy.begin() + i);

			//���ꂽ���߂�
			i--;
		}
	}
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::Render()
{
	//�X�e�[�W�`��
	m_stage->Draw(m_view, m_proj);

	//�d�͕`��
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->DrawGravity(m_view, m_proj);
	}

	//�v���C���[�`��
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		if (m_player[i]->InvincibleTime() % 2 == 0)
		{
			m_player[i]->Draw(m_view, m_proj);
		}
		m_player[i]->DrawHpGauge(m_view, m_proj);
	}

	m_summonEffect->Draw(m_view, m_proj);
	m_blastEffect->Draw(m_view, m_proj);

	//�G�`��
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		m_enemy[i]->Draw(m_view,m_proj);
	}
}



//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�����蔻��
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::Collision()
{
	//�����蔻��
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		//�G�Əd�͂��������Ă��邩�ǂ���
		bool isHitGravity[2] = { false,false };

		for (int j = 0; j < Player::MAX_PLAYER; j++)
		{
			//�G�Əd�͂̓����蔻��
			isHitGravity[j] = Collision(m_enemy[i], m_player[j]->GetGravity());

			//�v���C���[�����G�Ȃ�Γ����蔻����΂�
			if (m_player[j]->InvincibleTime() > 0){	break;}

			//�G�ƃv���C���[�̓����蔻��
			if (Collision(m_enemy[i], m_player[j]))
			{
				m_player[j]->TakeDamage(1);
				m_player[j]->InvincibleTime(60);
			}
		}

		//�G���m�̓����蔻��
		for (int j = i + 1; j < static_cast<int>(m_enemy.size()); j++)
		{
			if (Collision(m_enemy[i], m_enemy[j]))
			{
				//�ǂ��炩��������ԂȂ�Η���
				if (m_enemy[i]->IsConfused() || m_enemy[j]->IsConfused())
				{
					m_enemy[i]->Dead();
					m_enemy[j]->Dead();
				}
			}
		}

		//���݌����̏���
		if (IsSandwiched(isHitGravity, m_enemy[i])) { m_enemy[i]->Fluster(); }
	}
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�I�u�W�F�N�g���m�̓����蔻��
//�b����  :�I�u�W�F�N�g�P(Object*)
//�b����  :�I�u�W�F�N�g�Q(Object*)
//�b�߂�l:�������Ă����� true(bool)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
bool PlayScene::Collision(Object* obj,Object* obj2)
{
	using namespace ShunLib;

	Vec3 pos1 = obj->Pos();
	Vec3 pos2 = obj2->Pos();

	float x = pos1.m_x - pos2.m_x;
	float y = pos1.m_z - pos2.m_z;
	float r = obj->Radius() + obj2->Radius();

	if (x*x + y*y <= r*r){
		return true;
	}

	return false;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�d�͂Ƃ̓����蔻��
//�b����  :�I�u�W�F�N�g(Object*)
//�b����  :�d��		   (Gravity*)
//�b�߂�l:�������Ă����� true(bool)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
bool PlayScene::Collision(Object* obj, Gravity* gra)
{
	using namespace ShunLib;

	Vec3 pos1 = obj->Pos();
	Vec3 pos2 = gra->Pos();

	float x = pos1.m_x - pos2.m_x;
	float y = pos1.m_z - pos2.m_z;
	float r = obj->Radius() + gra->Radius();

	if (x*x + y*y <= r*r){
		//�Ώۂ��d�͂ň����񂹂�
		ShunLib::Vec3 pos = obj->Pos();
		gra->Attract(&pos);
		obj->Pos(pos);
		return true;
	}

	return false;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :���܂�Ă��邩�ǂ����̔���
//�b����  :�d�͂Ƃ̓����蔻��̌���(bool[])
//�b�߂�l:���܂�Ă�����true(bool)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
bool PlayScene::IsSandwiched(bool isHitGravity[], Enemy* enemy)
{
	using namespace ShunLib;

	int hitNum = 0;

	//�������Ă��鐔���J�E���g
	for (int i = 0; i < Player::MAX_PLAYER; i++){
		if (isHitGravity[i]) { hitNum++; }
	}

	//�Por�O�Ȃ�Δ�����
	if (hitNum <= 1) { return false; }


	//�x�N�g�������߂�
	Vec3 v1 = m_player[0]->Pos() - enemy->Pos();
	Vec3 v2 = m_player[1]->Pos() - enemy->Pos();

	//���K��
	v1.Normalize();
	v2.Normalize();

	//���ς����߂�
	float dot = v1.GetDirectVec3().Dot(v2.GetDirectVec3());

	//�p�x�����߂�
	float angle = ToAngle(acos(dot));

	//�p�x�����ȏ�Ȃ狲�܂�Ă���
	if (std::abs(angle) >= 90.0f)
	{
		return true;
	}

	return false;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�G�̐���
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::CreateEnemy()
{
	//���������p
	std::random_device random;
	std::mt19937 mt(random());

	//�����̒l�𐧌�
	std::uniform_real_distribution<float> num(STAGE_LEFT, STAGE_RIGHT);

	//�G�����@delete �[> ~PlayScene
	m_enemy.push_back(new Enemy(L"CModel\\Enemy.cmo", ShunLib::Vec3(num(mt), 0.0f,STAGE_BOTTOM),ShunLib::Vec3(0.0f,0.0f,0.1f)));

	m_summonEffect->SetDraw();
	m_summonEffect->SetScale(1.5f);
	m_summonEffect->SetPos(m_enemy.back()->Pos());
}

