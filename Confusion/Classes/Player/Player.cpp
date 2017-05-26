//************************************************/
//* @file  :Player.cpp
//* @brief :�v���C���[�̃\�[�X�t�@�C��
//* @date  :2017/05/17
//* @author:S.Katou
//************************************************/
#include "Player.h"
#include "../Wrapper/GamePad/GamePadManager.h"
#include "../Wrapper/ConstantNumber/MacroConstants.h"

//�v���C���[�ő吔
const int Player::MAX_PLAYER = 2;

//���x�{��
const float Player::SPD_MAGNIFICATION = 8.0f;
const int Player::MAX_HP = 20;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t*)
//�b����  :�������W	 (ShunLib::Vec3)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Player::Player(const wchar_t* model, ShunLib::Vec3 pos, int gamePadNum, ShunLib::DIRECTION_2D stick)
	: Object(model, pos)
	, m_gamePadNum(gamePadNum)
	, m_stick(stick)
	, m_gravityScale(0.1f)
	, m_hp(MAX_HP)
	, m_invincibleTime(0)
{
	m_gamePad = GamePadManager::GetInstance();

	m_radius = 0.8f;

	//delete -> ~Player
	m_gravity = new Gravity(L"Effect\\gravity.png");
	m_gravity->Radius(m_gravityScale);

	//delete -> ~Player
	m_hpGauge = new HPGauge(m_hp, *m_pos, ShunLib::Vec3(2.0f, 0.5f, 1.0f), ShunLib::Vec3(90.0f, 0.0f, 0.0f));
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Player::~Player()
{
	DELETE_POINTER(m_gravity);
	DELETE_POINTER(m_hpGauge);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Player::Update()
{
	//���x�X�V
	UpdateSpd();

	//�ړ�
	*m_pos = *m_pos + (*m_spd * SPD_MAGNIFICATION /60.0f);

	//���G���Ԍ���
	if (m_invincibleTime > 0)
	{
		m_invincibleTime--;
	}

	//�d�͊֘A�̍X�V
	UpdateGravity();
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`��
//�b����  :�r���[�s��		   (ShunLib::Matrix)
//�b����  :�v���W�F�N�V�����s��(ShunLib::Matrix)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Player::Draw(const ShunLib::Matrix & view, const ShunLib::Matrix & proj)
{
	//����ł�����`�悵�Ȃ�
	if (m_hp <= 0) { return; }

	//���G���͓_�ł�����
	if (m_invincibleTime % 2 == 0)
	{
		Object::Draw(view, proj);
	}

	this->DrawHpGauge(view, proj);
}



//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :HP�Q�[�W�̕`��
//�b����  :�r���[�s��		   (ShunLib::Matrix)
//�b����  :�v���W�F�N�V�����s��(ShunLib::Matrix)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Player::DrawHpGauge(const ShunLib::Matrix& view, const ShunLib::Matrix& proj)
{
	using namespace ShunLib;
	m_hpGauge->HP(m_hp);
	m_hpGauge->Pos(*m_pos);
	m_hpGauge->Draw(view, proj);
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�v���C���[���X�e�[�W�O�ɏo�Ȃ��悤�ɂ���
//�b����  :�X�e�[�W�̏�(float)
//�b����  :�X�e�[�W�̉�(float)
//�b����  :�X�e�[�W�̉E(float)
//�b����  :�X�e�[�W�̍�(float)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Player::Clamp(float top, float bottom, float right, float left)
{
	//�y����������
	if (m_pos->m_z > top)
	{
		m_pos->m_z = top;
	}

	//�y����������
	if (m_pos->m_z < bottom)
	{
		m_pos->m_z = bottom;
	}


	//�w����������
	if (m_pos->m_x > right)
	{
		m_pos->m_x = right;
	}

	//�w����������
	if (m_pos->m_x < left)
	{
		m_pos->m_x = left;
	}
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :���x�̍X�V
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Player::UpdateSpd()
{
	using namespace ShunLib;

	auto state = m_gamePad->Get(m_gamePadNum);

	//���x��ݒ�
	//�y���͍��W�n�̊֘A�Ń}�C�i�X���|����
	switch (m_stick)
	{
	case DIRECTION_2D::RIGHT://�E�X�e�B�b�N
		m_spd->m_x = state.thumbSticks.rightX;
		m_spd->m_z = -(state.thumbSticks.rightY);
		break;

	case DIRECTION_2D::LEFT://���X�e�B�b�N
		m_spd->m_x = state.thumbSticks.leftX;
		m_spd->m_z = -(state.thumbSticks.leftY);
		break;

	default://����ȊO�͍�
		m_spd->m_x = state.thumbSticks.leftX;
		m_spd->m_z = -(state.thumbSticks.leftY);
		break;
	}

}



//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�d�͊֘A�̍X�V
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Player::UpdateGravity()
{
	//�d�͈ʒu���ړ�
	m_gravity->Pos(m_pos->m_x, -1.0f, m_pos->m_z);

	//�d�͂̊g�嗦�̍X�V
	UpdateGravityScale();

	//�d�͂�ݒ�
	m_gravity->Radius(m_gravityScale);

	//�d�͍X�V
	m_gravity->Update();
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�d�͂̊g�嗦�X�V
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Player::UpdateGravityScale()
{
	using namespace ShunLib;

	auto state = m_gamePad->Get(m_gamePadNum);

	//�{�^����������Ă��邩�ǂ���
	bool isPushed = false;

	//�X�e�B�b�N�ƑΉ�����{�^���Ŕ�����Ƃ�
	switch (m_stick)
	{
	case DIRECTION_2D::RIGHT://�E�X�e�B�b�N
		isPushed = state.IsRightShoulderPressed();
		break;

	case DIRECTION_2D::LEFT://���X�e�B�b�N
		isPushed = state.IsLeftShoulderPressed();
		break;

	default://����ȊO�͍�
		isPushed = state.IsLeftShoulderPressed();
		break;
	}

	//�����Ă���ԍL���葱����
	if (isPushed)
	{
		m_gravityScale += 0.1f;
	}
	else
	{
		m_gravityScale -= 0.2f;
	}

	//�k���������Ȃ��悤�ɂ���
	if (m_gravityScale < 0.0f)
	{
		m_gravityScale = 0.0f;
	}
	//�g�債�����Ȃ��悤�ɂ���
	if (m_gravityScale > 10.0f)
	{
		m_gravityScale = 10.0f;
	}
}

