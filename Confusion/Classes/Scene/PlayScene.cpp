//************************************************/
//* @file  :PlayScene.cpp
//* @brief :�v���C��ʂ̃N���X
//* @date  :2017/05/13
//* @author:S.Katou
//************************************************/
#include <random>
#include "PlayScene.h"
#include "../Sound/PlayScene.h"
#include "../Sound/ADX2Le.h"
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
	:m_isStarted(false)
	,m_isEnded(false)
	,m_stageLife(5)
{
	using namespace ShunLib;
	m_view = Matrix::CreateLookAt(Vec3(0.0f, 30.0f, 40.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 200.0f);

	m_hpGauge = new HPGauge(m_stageLife, Vec3(0.0f, 1.0f, 21.2f), Vec3(27.5f, 1.0f, 2.0f), Vec3(-55.0f, 0.0f, 0.0f));

	//�v���C���[����  delete �[> ~PlayScene
	m_player	= new Player*[Player::MAX_PLAYER];
	m_player[0] = new Player(L"CModel\\Player.cmo", Vec3(-5.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\PlayerB.cmo", Vec3(5.0f, 0.0f, 0.0f), 0, RIGHT);

	//���j�G�t�F�N�g����
	m_blastEffect = new ShunLib::Effect(L"Effect\\Blast.efk", 0,512);
	
	//���@�w�̐��������_���Ō���
	m_maxMagic = rand() % 5 + 2;
	
	//���@�w�̐���  delete �[> ~PlayScene
	m_magic = new SummonMagic*[m_maxMagic];
	for (int i = 0; i < m_maxMagic; i++)
	{
		m_magic[i] = new SummonMagic(Vec3(static_cast<float>(std::rand() % 20-10.0f),0.0f, -(static_cast<float>(std::rand() % 40 + 10))),
									 rand()%500+30,
									 i*20,5.0f);
	}

	//�X�e�[�W����
	m_stage = new Stage;

	ADX2Le::LoadAcb("Sounds\\PlayScene.acb");
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
PlayScene::~PlayScene()
{
	//�v���C���[�폜
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		if (m_player[i] != nullptr) { delete m_player[i]; }
	}
	if (m_player != nullptr) { delete[] m_player; }

	//���@�w�̍폜
	for (int i = 0; i < m_maxMagic; i++)
	{
		if (m_magic[i] != nullptr) { delete m_magic[i]; }
	}
	if (m_magic != nullptr) { delete[] m_magic; }

	//�X�e�[�W�폜
	if (m_stage != nullptr){ delete m_stage; }
	
	//HP�Q�[�W�폜
	if (m_hpGauge != nullptr) { delete m_hpGauge; }	
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::Update()
{
	//�v���C�O�̏���
	if (!m_isStarted)
	{
		PlayAgo();
	}

	//�v���C���̏���
	if (m_isStarted
	&& !m_isEnded)
	{
		PlayMain();
	}


	//�Q�[���I�[�o�[
	if (IsGameOver())
	{
		if (PlayGameOver())
		{
			m_nextScene = Scene::OVER;
		}
	}

	//�Q�[���N���A
	if (IsCleared())
	{
		if (PlayClear())
		{
			m_nextScene = Scene::CLEAR;
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

	//���@�w�`��
	for (int i = 0; i < m_maxMagic; i++)
	{
		m_magic[i]->Draw(m_view, m_proj);
	}

	//�G�t�F�N�g�\��
	m_blastEffect->Draw(m_view, m_proj);

	//�v���C���[�`��
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		if (m_player[i]->InvincibleTime() % 2 == 0)
		{
			m_player[i]->Draw(m_view, m_proj);
		}
		m_player[i]->DrawHpGauge(m_view, m_proj);
	}

	//�G�`��
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		m_enemy[i]->Draw(m_view,m_proj);		
	}

	//�g�o�Q�[�W�`��
	m_hpGauge->HP(m_stageLife);
	m_hpGauge->Draw(m_view, m_proj);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�v���C�J�n�O�̏���
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::PlayAgo()
{
	m_isStarted = true;
	for (int i = 0; i < m_maxMagic; i++)
	{
		//���@�w�X�V
		m_magic[i]->Update();
		
		//���@�w���o�����Ă��Ȃ�������n�܂�Ȃ�
		if (!m_magic[i]->IsStarted())
		{
			m_isStarted = false;
		}
	}
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�v���C���̏���
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::PlayMain()
{

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
		
		//�G�����ɓ������Ď��񂾂�_���[�W	
		if (m_enemy[i]->Dead(STAGE_TOP, STAGE_BOTTOM, STAGE_RIGHT, STAGE_LEFT) == ShunLib::DIRECTION_2D::BOTTOM)
		{
			m_stageLife--;
		}
		
		//����ł������̏���
		if (m_enemy[i]->IsDead())
		{
			//���j�G�t�F�N�g�ݒ�
			m_blastEffect->SetDraw(m_enemy[i]->Pos() + ShunLib::Vec3(0.0f, 1.0f, 0.0f));
			ADX2Le::Play(CRI_PLAYSCENE_BOMB2);

			//�G�폜
			m_enemy.erase(m_enemy.begin() + i);

			//���ꂽ���߂�
			i--;
		}
	}

	//���@�w�X�V
	for (int i = 0; i < m_maxMagic; i++)
	{
		m_magic[i]->Update();
	}

	//�G����
	CreateEnemy();

	//�����蔻��
	Collision();
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�N���A�̏���
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
bool PlayScene::PlayClear()
{
	m_isEnded = true;
	static int b = 0;
	b++;
	if (b < 260)
	{
		return false;
	}
	return true;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�Q�[���I�[�o�[�̏���
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
bool PlayScene::PlayGameOver()
{
	m_isEnded = true;

	static int a = 0;
	a++;
	if (a < 260)
	{
		return false;
	}
	return true;
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
			isHitGravity[j] = Collision(m_enemy[i].get(), m_player[j]->GetGravity());

			//�v���C���[�����G�Ȃ�Γ����蔻����΂�
			if (m_player[j]->InvincibleTime() > 0){	break;}

			//�G�ƃv���C���[�̓����蔻��
			if (Collision(m_enemy[i].get(), m_player[j]))
			{
				m_player[j]->TakeDamage(1);
				m_player[j]->InvincibleTime(60);

				m_enemy[i]->Dead();
			}
		}

		//�G���m�̓����蔻��
		for (int j = i + 1; j < static_cast<int>(m_enemy.size()); j++)
		{
			if (Collision(m_enemy[i].get(), m_enemy[j].get()))
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
		if (IsSandwiched(isHitGravity, m_enemy[i].get())) { m_enemy[i]->Fluster(); }
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

	if (x*x + y*y <= r*r)
	{
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
	if (std::abs(angle) >= 80.0f)
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
	for (int i = 0; i < m_maxMagic; i++)
	{
		//���@�w�������\�Ȃ�ΓG����
		if (m_magic[i]->CanSummon())
		{
			m_enemy.push_back(m_magic[i]->Create());
		}
	}
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�Q�[���N���A����
//�b����  :�Ȃ�(void)
//�b�߂�l:�N���A������true(bool)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
bool PlayScene::IsCleared()
{
	for (int i = 0; i < m_maxMagic; i++)
	{
		//���@�w����ł����݂��Ă�����NOT CLEAR
		if (m_magic[i]->Scale() > 0.0f)
		{
			return false;
		}
	}

	//�G�����݂��Ă�����NOT CLEAR
	if (!m_enemy.empty())
	{
		return false;
	}
	return true;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�Q�[���I�[�o�[����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Q�[���I�[�o�[��true(bool)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
bool PlayScene::IsGameOver()
{
	//�v���C���[���Е��ł����񂾂�GameOver
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		if (m_player[i]->Hp() <= 0)
		{
			return true;
		}
	}

	//�X�e�[�W�̃��C�t���O�ɂȂ�����GameOver
	if (m_stageLife <= 0)
	{
		return true;
	}
	return false;
}


