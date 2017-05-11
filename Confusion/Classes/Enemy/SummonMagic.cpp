//************************************************/
//* @file  :SummonMagic.cpp
//* @brief :�G���������閂�@�w�N���X
//* @date  :2017/05/10
//* @author:S.Katou
//************************************************/
#include "SummonMagic.h"
#include <random>

SummonMagic::SummonMagic(ShunLib::Vec3 pos, int interval, int firstInterval, float scale)
	: m_interval(interval)
	, m_intervaCnt(0)
	, m_firstInterval(firstInterval)
	, m_firstIntervaCnt(0)
	, m_scale(0.0f)
	, m_maxScale(scale)
	, m_angle(0.0f)
	, m_isStart(false)
{
	m_texture      = new ShunLib::Texture(L"Images\\magic.png");
	m_pos          = new ShunLib::Vec3(pos);
	m_summonEffect = new ShunLib::Effect(L"Effect\\Magic.efk",60);
}

SummonMagic::~SummonMagic()
{
	delete m_texture;
	delete m_pos;
	delete m_summonEffect;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�G�𐶐�����
//�b����  :�Ȃ�(void)
//�b�߂�l:�G(shared_ptr<Enemy>)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
std::shared_ptr<Enemy> SummonMagic::Create()
{
	//ShunLib::Vec3 randPos((std::rand() % static_cast<int>(m_scale * 20)) / 10.0f - m_scale,
	//					  0.0f, 
	//					  (std::rand() % static_cast<int>(m_scale * 20)) / 10.0f - m_scale);
	ShunLib::Vec3 randPos(0.0f,0.0f,0.0f);
	//�G����
	std::shared_ptr<Enemy>enemy = std::make_shared<Enemy>(L"CModel\\Enemy.cmo",
								  *m_pos+ randPos,
								  ShunLib::Vec3(0.0f, 0.0f, 0.1f));
	
	//�G�t�F�N�g�ݒ�
	m_summonEffect->SetDraw();
	m_summonEffect->SetScale(2.0f);
	m_summonEffect->SetPos(enemy->Pos());

	//�J�E���g���Z�b�g
	m_intervaCnt = 0;

	//�p���[�_�E��
	m_scale -= 0.1f;

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
	if (m_firstIntervaCnt<m_firstInterval)
	{
		m_firstIntervaCnt++;
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
		m_intervaCnt++;
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
		* Matrix::CreateTranslation(*m_pos);

	m_texture->Draw(world, view, proj);

	m_summonEffect->Draw(view, proj);
}
