//************************************************/
//* @file  :PlayScene.cpp
//* @brief :�v���C��ʂ̃N���X
//* @date  :2017/05/17
//* @author:S.Katou
//************************************************/
#include <random>
#include "PlayScene.h"
#include "../Sound/PlayScene.h"
#include "../Sound/TitleScene.h"
#include "../Sound/ADX2Le.h"
#include "../Wrapper/Vec3/Vec3.h"
#include "../GameMain.h"
#include "../Conversion/Conversion.h"
#include "../Enemy/BossMagic.h"

//�X�e�[�W�̏㉺���E
const float PlayScene::STAGE_TOP    =  25.0f;
const float PlayScene::STAGE_BOTTOM = -30.0f;
const float PlayScene::STAGE_RIGHT  =  15.0f;
const float PlayScene::STAGE_LEFT   = -15.0f;


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
PlayScene::PlayScene()
	:m_isStarted(false)
	,m_isEnded(false)
	,m_stageHP(300)
{
	using namespace ShunLib;
	m_view = Matrix::CreateLookAt(Vec3(0.0f, 30.0f, 50.0f), Vec3::Zero, Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(GameMain::screenW / GameMain::screenH), 1.0f, 200.0f);


	//�v���C���[����  delete �[> ~PlayScene
	m_player	= new Player*[Player::MAX_PLAYER];
	m_player[0] = new Player(L"CModel\\Player.cmo", Vec3(-5.0f, 0.0f, 0.0f), 0, LEFT);
	m_player[1] = new Player(L"CModel\\PlayerB.cmo", Vec3(5.0f, 0.0f, 0.0f), 0, RIGHT);

	//�G�t�F�N�g����
	m_blastEffect = new ShunLib::Effect(L"Effect\\Blast.efk", 0, 512*2);
	m_endEffect = new ShunLib::Effect(L"Effect\\GameClear2.efk", 120, 512);

	//�{�X���@�w����
	m_boss = std::make_unique<BossMagic>(ShunLib::Vec3(0.0f, 0.0f, STAGE_BOTTOM), 90, 0, 15.0f, 500);

	m_hpGauge = new HPGauge(m_stageHP, Vec3(0.0f, 0.0f, 26.7f), Vec3(29.5f, 1.0f, 2.0f), Vec3(-55.0f, 0.0f, 0.0f));
	m_bossGauge = new HPGauge(m_boss->HP(), Vec3(0.0f, 26.0f, 26.7f), Vec3(10.5f, 0.8f, 1.0f), Vec3(-55.0f, 0.0f, 0.0f));

	//�X�e�[�W����
	m_stage = new Stage;

	m_createMagicTimer = new Timer();
	m_createMagicTimer->SetTime(600);

	ADX2Le::LoadAcb("Sounds\\PlayScene.acb", "Sounds\\PlayScene.awb");
	ADX2Le::Play(CRI_PLAYSCENE_DAMONS_DANCE);
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


	//�X�e�[�W�폜
	if (m_stage != nullptr) { delete m_stage; }

	//HP�Q�[�W�폜
	if (m_hpGauge != nullptr) { delete m_hpGauge; }
	if (m_bossGauge != nullptr) { delete m_bossGauge; }

	//�G�t�F�N�g�폜
	if (m_blastEffect != nullptr) { delete m_blastEffect; }
	if (m_endEffect != nullptr) { delete m_endEffect; }
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
	if (m_isStarted)
	{
		if (!m_isEnded)
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
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::Render()
{
	//�X�e�[�W�̕`��
	DrawStage();

	//���@�w�`��
	std::vector<std::shared_ptr<SummonMagic>>::iterator magicItr;
	for (magicItr = m_magic.begin(); magicItr != m_magic.end(); magicItr++)
	{
		(*magicItr)->Draw(m_view, m_proj);
	}

	//�d�͕`��i�`�揇�̊֌W��Player�ƕ�����j
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->DrawGravity(m_view, m_proj);
	}

	//�G�t�F�N�g�\��
	if (m_blastEffect != nullptr){	m_blastEffect->Draw(m_view, m_proj);}


	//�v���C���[�`��
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_player[i]->Draw(m_view, m_proj);
	}

	//�G�`��
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++){	m_enemy[i]->Draw(m_view,m_proj);}

	//�g�o�Q�[�W�`��
	if (m_stageHP > 0)
	{
		m_hpGauge->HP(m_stageHP);
		m_hpGauge->Draw(m_view, m_proj);
	}

	//�{�X���@�w�����݂���Ԃg�o�Q�[�W��\��
	if (!(m_boss->IsDead()))
	{
		m_bossGauge->HP(m_boss->HP());
		m_bossGauge->Draw(m_view, m_proj);
	}

	//�G�t�F�N�g�`��
	if (!m_endEffect->IsEnded())   { m_endEffect->Draw(m_view, m_proj); }
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�G�֘A�̍X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::UpdateEnemy()
{
	for (int i = 0; i < static_cast<int>(m_enemy.size()); i++)
	{
		m_enemy[i]->Update();
		int dir = m_enemy[i]->Dead(STAGE_TOP, STAGE_BOTTOM, STAGE_RIGHT, STAGE_LEFT);
		//�G�����ɓ������Ď��񂾂�_���[�W	
		if (dir == ShunLib::DIRECTION_2D::BOTTOM)
		{
			m_stageHP--;
		}
		//�G�����ɓ������Ď��񂾂�{�X���@�w�Ƀ_���[�W	
		if (dir == ShunLib::DIRECTION_2D::TOP)
		{
			m_boss->TakeDamage(20);
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
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :���@�w�֘A�̍X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::UpdateMagic()
{
	//���@�w�X�V
	std::vector<std::unique_ptr<SummonMagic>>::iterator magicItr;
	for (int i = 0; i < static_cast<int>(m_magic.size()); i++)
	{
		m_magic[i]->Update();
		if (!(m_magic[i]->IsStarted())) { continue; }

		if (m_magic[i]->CanSummon())
		{
			m_enemy.push_back(m_magic[i]->SummonEnemy());
		}

		if (m_magic[i]->Scale() <= 0.0f) { m_magic.erase(m_magic.begin() + i); i--; }
	}

	//��莞�Ԃ��Ƃɖ��@�w�����j
	if (m_createMagicTimer->IsEnded())
	{
		m_createMagicTimer->ResetCount();
		m_magic.push_back(m_boss->CreateMagic(STAGE_LEFT,STAGE_RIGHT,0.0f,STAGE_BOTTOM));
	}
	m_boss->Update();
	if (m_boss->CanSummon()) { m_enemy.push_back(m_boss->SummonEnemy()); }

}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�e�[�W�֘A�̕`�揈��
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::DrawStage()
{
	//�X�e�[�W�`��@
	//�ԂɃ{�X���@�w������
	using namespace ShunLib;
	using namespace std;

	//�X�e�[�W���`��
	Matrix stageScale = Matrix::CreateScale(Vec3(120.0f, 1.0f, abs(STAGE_BOTTOM) * 2));
	m_stage->Draw(stageScale*Matrix::CreateTranslation(Vec3(0.0f, 0.0f, STAGE_BOTTOM)), m_view, m_proj);

	if (m_boss != nullptr)
	{
		m_boss->Draw(m_view, m_proj);
	}

	//�X�e�[�W�`�� �\�����o�O��̂ŏ����������炷
	m_stage->Draw(stageScale*Matrix::CreateTranslation(Vec3(0.0f, 0.01f, 0.0f)), m_view, m_proj);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�v���C�J�n�O�̏���
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::PlayAgo()
{
	m_isStarted = true;
	m_boss->Update();
	if (!(m_boss->IsStarted()))
	{
		m_isStarted = false;
		return;
	}

	std::vector<std::shared_ptr<SummonMagic>>::iterator magicItr;
	for (magicItr = m_magic.begin(); magicItr != m_magic.end(); magicItr++)
	{
		//���@�w�X�V
		(*magicItr)->Update();
		
		//���@�w���o�����Ă��Ȃ�������n�܂�Ȃ�
		if (!((*magicItr)->IsStarted()))
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
	UpdateEnemy();

	//���@�w�X�V
	UpdateMagic();

	//�^�C�}�[�J�E���g
	m_createMagicTimer->Update();

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

	if (m_endEffect->IsEnded())
	{
		return true;
	}
	return false;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�Q�[���I�[�o�[�̏���
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
bool PlayScene::PlayGameOver()
{
	m_isEnded = true;

	if (m_endEffect->IsEnded())
	{
		return true;
	}
	return false;
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
				ADX2Le::Play(CRI_PLAYSCENE_BOMB2);
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
//�b�@�\  :���@�w�̐���
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::CreateMagic()
{	
	float randPosX = static_cast<float>(std::rand() % std::abs((int)(STAGE_RIGHT + STAGE_LEFT + 1)));
	float randPosZ= -(static_cast<float>(std::rand() % std::abs((int)STAGE_BOTTOM)));
	int summonInterval = std::rand() % 500 + 30;
	int firstInterval = std::rand() % 120 + 120;
	float scale = (rand() % 100 + 1) / 10.0f;

	m_magic.push_back(std::make_unique<SummonMagic>(
		ShunLib::Vec3(randPosX,0.0f,randPosZ),
		summonInterval,
		firstInterval,
		scale));
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :���ׂĂ̖��@�w������
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void PlayScene::DeleteAllMagic()
{
	//�G�̍폜
	while (!m_enemy.empty())
	{
		std::shared_ptr<Enemy> enemy = m_enemy.back();

		//���j�G�t�F�N�g�ݒ�
		m_blastEffect->SetDraw(enemy->Pos() + ShunLib::Vec3(0.0f, 1.0f, 0.0f));
		ADX2Le::Play(CRI_PLAYSCENE_BOMB2);
		m_enemy.pop_back();
	}

	//���@�w�̍폜
	while (!m_magic.empty())
	{
		m_magic.pop_back();
	}
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�Q�[���N���A����
//�b����  :�Ȃ�(void)
//�b�߂�l:�N���A������true(bool)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
bool PlayScene::IsCleared()
{
	//�{�X�̂g�o���O�ɂȂ�����N���A
	if (m_boss->HP() <= 0)
	{
		if (!m_isEnded)
		{
			//�S�Ă̖��@�w������
			DeleteAllMagic();

			//�{�X����
			m_boss->Dead();

			//�G�t�F�N�g�Đ�
			m_endEffect->SetDraw(ShunLib::Vec3(0.0f, 1.0f, STAGE_BOTTOM));
			m_endEffect->SetScale(8.0f);
			m_endEffect->SetSpd(0.3f);

			//���ʉ�
			ADX2Le::Play(CRI_PLAYSCENE_MAGIC_CHANT2);
			m_isEnded = true;
		}		
		return true;
	}
	return false;
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
			if (!m_isEnded)
			{
				m_endEffect->SetDraw(m_player[i]->Pos());
				m_endEffect->SetScale(1.5f);
				m_endEffect->SetSpd(0.5f);
				ADX2Le::Play(CRI_PLAYSCENE_MAGIC_CHANT2);

				m_isEnded = true;
			}
			return true;
		}
	}

	//�X�e�[�W�̃��C�t���O�ɂȂ�����GameOver
	if (m_stageHP <= 0)
	{
		if (!m_isEnded)
		{
			ADX2Le::Play(CRI_PLAYSCENE_MAGIC_CHANT2);

			//�G�t�F�N�g�Đ�
			m_endEffect->SetDraw(ShunLib::Vec3(0.0f, 1.0f, STAGE_TOP));
			m_endEffect->SetScale(8.0f);
			m_endEffect->SetSpd(0.3f);

			m_isEnded = true;
		}
		return true;
	}
	return false;
}


