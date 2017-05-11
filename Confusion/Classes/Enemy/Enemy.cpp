//************************************************/
//* @file  :Enemy.cpp
//* @brief :�G�̃\�[�X�t�@�C��
//* @date  :2017/05/06
//* @author:S.Katou
//************************************************/
#include "Enemy.h"
#include "../Wrapper/ConstantNumber/ConstantNumber.h"

//���x�{��
const float Enemy::SPD_MAGNIFICATION = 3.0f;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t*)
//�b����  :�������W	 (ShunLib::Vec3)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Enemy::Enemy(const wchar_t* model, ShunLib::Vec3 pos, ShunLib::Vec3 spd)
	: Object(model,pos,spd)
	, m_isDead(false)
	, m_confusedTime(0)
	, m_isConfused(false)
{
	m_radius = 1.0f;
	m_firstSpd = spd;

	m_confusionEffect = new ShunLib::Effect(L"Effect\\Confusion.efk",130,256,true);	
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Enemy::~Enemy()
{
	delete m_confusionEffect;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Enemy::Update()
{
	//�ړ�
	*m_pos = *m_pos + (*m_spd * SPD_MAGNIFICATION / 60.0f);

	//�������Ԍo��
	if (m_isConfused)
	{
		m_confusedTime--;
	}

	//���Ԍo�߂ō�����ԉ���
	if (m_confusedTime <= 0)
	{
		*m_spd = m_firstSpd;
		m_confusedTime = 0;
		m_isConfused = false;
	}
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`��
//�b����  :�r���[�s��		   (ShunLib::Matrix)
//�b����  :�v���W�F�N�V�����s��(ShunLib::Matrix)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Enemy::Draw(const ShunLib::Matrix& view, const ShunLib::Matrix& proj)
{
	using namespace ShunLib;
	
	Object::Draw(view,proj);

	//�������Ă�����G�t�F�N�g�\��
	if (m_isConfused)
	{
		m_confusionEffect->SetScale(0.5f);
		m_confusionEffect->SetRotate(ShunLib::Vec3::UnitX, 30.0f);
		m_confusionEffect->SetPos(*m_pos+Vec3(0.0f,3.0f,0.0f));
		m_confusionEffect->DrawLoop(view, proj);
	}
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :���x�x�N�g������]������
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Enemy::Fluster()
{
	m_isConfused = true;

	//���x�x�N�g������]������
	m_spd->m_x = cosf(static_cast<float>(m_confusedTime/30));
	m_spd->m_z = sinf(static_cast<float>(m_confusedTime/30));

	//�������Ԃ����Z 0.5�b
	m_confusedTime += 30;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�͈͊O�ɏo���玀
//�b����  :�X�e�[�W�̏�(float)
//�b����  :�X�e�[�W�̉�(float)
//�b����  :�X�e�[�W�̉E(float)
//�b����  :�X�e�[�W�̍�(float)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
int Enemy::Dead(float top, float bottom, float right, float left)
{

	//�y����������
	if (m_pos->m_z > top)
	{
		Dead();	
		return ShunLib::DIRECTION_2D::BOTTOM;
	}

	//�y����������
	if (m_pos->m_z < bottom)
	{
		Dead();
		return ShunLib::DIRECTION_2D::TOP;
	}


	//�w����������
	if (m_pos->m_x > right)
	{
		Dead();
		return ShunLib::DIRECTION_2D::RIGHT;
	}

	//�w����������
	if (m_pos->m_x < left)
	{
		Dead();
		return ShunLib::DIRECTION_2D::LEFT;
	}

	return -1;
}
