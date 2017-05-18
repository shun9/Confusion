//************************************************/
//* @file  :SummonMagic.cpp
//* @brief :�G���������閂�@�w�N���X
//* @date  :2017/05/10
//* @author:S.Katou
//************************************************/
#include "SummonMagic.h"
#include <random>
#include "../Timer/Timer.h"
#include "../RandomNumber/RandomNumber.h"

SummonMagic::SummonMagic(ShunLib::Vec3 pos, int interval, int firstInterval, float scale, float summonPower)
	: m_scale(0.0f)
	, m_maxScale(scale)
	, m_angle(0.0f)
	, m_isStart(false)
	, m_summonPower(summonPower)
{
	using namespace ShunLib;
	m_texture	   = new Texture(L"Images\\magic.png");
	m_pos          = new Vec3(pos);
	m_summonEffect = new Effect(L"Effect\\Magic.efk",60);
	m_summonIntervalTimer = new Timer();
	m_summonIntervalTimer->SetTime(interval);
	m_firstIntervalTimer = new Timer();
	m_firstIntervalTimer->SetTime(firstInterval);
}

SummonMagic::~SummonMagic()
{
	delete m_texture;
	delete m_pos;
	delete m_summonEffect;

	delete m_summonIntervalTimer;
	delete m_firstIntervalTimer;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�G�𐶐�����
//�b����  :�Ȃ�(void)
//�b�߂�l:�G(shared_ptr<Enemy>)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
std::shared_ptr<Enemy> SummonMagic::SummonEnemy()
{
	using namespace ShunLib;

	RandomNumber randNum;
	Vec3 randPos(randNum(-m_scale,m_scale),0.0f, randNum(-m_scale, m_scale));
	Vec3 randSpd(0.0f, 0.0f, randNum(0.1f, 100.0f));

	//�G����
	std::shared_ptr<Enemy>enemy = std::make_shared<Enemy>(L"CModel\\Enemy.cmo",
								  *m_pos+ randPos,
		randSpd);
	
	//�G�t�F�N�g�ݒ�
	m_summonEffect->SetDraw();
	m_summonEffect->SetScale(2.0f);
	m_summonEffect->SetPos(enemy->Pos());

	//�J�E���g���Z�b�g
	m_summonIntervalTimer->ResetCount();

	//�p���[�_�E��
	m_scale -= m_summonPower;

	return enemy;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void SummonMagic::Update()
{
	//�J�n�܂ő҂�
	if (!(m_firstIntervalTimer->IsEnded()))
	{
		m_firstIntervalTimer->Update();
		return;
	}

	//��]
	m_angle += 1.0f;
	if (m_angle >= 360.0f)
	{
		m_angle = 0.0f;
	}

	//�����J�n�܂ő҂�
	if (m_isStart)
	{
		m_summonIntervalTimer->Update();
	}

	if (!m_isStart)
	{
		m_scale += 0.1f;
		if (m_scale >= m_maxScale)
		{
			m_isStart = true;
		}
	}
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :�r���[�s��		   (ShunLib::Matrix)
//�b����  :�v���W�F�N�V�����s��(ShunLib::Matrix)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void SummonMagic::Draw(const ShunLib::Matrix& view, const ShunLib::Matrix& proj)
{
	using namespace ShunLib;

	Matrix world;
	world = Matrix::CreateScale(m_scale * 2)
		  * Matrix::CreateRotationY(m_angle)
		  * Matrix::CreateTranslation(*m_pos+Vec3(0.0f,1.0f,0.0f));

	m_texture->Draw(world, view, proj);

	m_summonEffect->Draw(view, proj);
}
