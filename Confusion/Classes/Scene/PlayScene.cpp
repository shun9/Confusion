//************************************************/
//* @file  :PlayScene.cpp
//* @brief :�v���C��ʂ̃\�[�X
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#include "PlayScene.h"
#include "../Wrapper/Vec3/Vec3.h"
#include "../GameMain.h"

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
PlayScene::PlayScene()
{
	using namespace ShunLib;
	m_view = Matrix::CreateLookAt(Vec3(0.0f, 10.0f, 13.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(90.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 100.0f);

	//�v���C���[����  delete �[> ~PlayScene
	m_player = new Player*[Player::MAX_PLAYER];
	m_player[0] = new Player(L"CModel\\Player.cmo", Vec3(-5.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\PlayerB.cmo", Vec3(5.0f, 0.0f, 0.0f), 0, RIGHT);

	//�G�����@delete �[> ~PlayScene
	m_enemy.push_back(new Enemy(L"CModel\\Enemy.cmo", Vec3(0.0f, 0.0f, 5.0f)));
	m_enemy.push_back(new Enemy(L"CModel\\Enemy.cmo", Vec3(0.0f, 0.0f, -5.0f)));
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
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::Update()
{

	//�v���C���[�X�V
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->Update();
	}

	//�G�X�V
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		m_enemy[i]->Update();
	}


	Collision();
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::Render()
{
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
	}

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
		for (int j = 0; j < Player::MAX_PLAYER; j++)
		{
			//�G�Əd�͂̓����蔻��
			if (Collision(m_enemy[i], m_player[j]->GetGravity()))
			{
				//�G���d�͂ň����񂹂�
				ShunLib::Vec3 pos = m_enemy[i]->Pos();
				m_player[j]->GetGravity()->Attract(&pos);
				m_enemy[i]->Pos(pos);
			}

			//�v���C���[�����G�Ȃ�Γ����蔻����΂�
			if (m_player[j]->InvincibleTime() > 0)
			{
				break;
			}

			//�G�ƃv���C���[�̓����蔻��
			if (Collision(m_enemy[i], m_player[j]))
			{
				m_player[j]->TakeDamage(1);
				m_player[j]->InvincibleTime(60);
			}
		}
	}
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�����蔻��
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
//�b�@�\  :�����蔻��
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

	if (x*x + y*y <= r*r)
	{
		return true;
	}

	return false;
}

