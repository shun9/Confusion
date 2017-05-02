//************************************************/
//* @file  :Player.cpp
//* @brief :�v���C���[�̃\�[�X�t�@�C��
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#include "Player.h"
#include "../Wrapper/GamePad/GamePadManager.h"

//�v���C���[�ő吔
const int Player::MAX_PLAYER = 2;

//���x�{��
const float Player::SPD_MAGNIFICATION = 6.0f;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t*)
//�b����  :�������W	 (ShunLib::Vec3)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Player::Player(const wchar_t* model, ShunLib::Vec3 pos, int gamePadNum,DIRECTION stick)
	: Object(model, pos)
	, m_gamePadNum(gamePadNum)
	, m_stick(stick)
	, m_gravityScale(0.1f)
	, m_hp(10)
	, m_invincibleTime(0)
{
	m_gamePad = GamePadManager::GetInstance();

	m_radius = 0.8f;

	m_gravity = new Gravity(L"Effect\\gravity.png");
	m_gravity->Radius(m_gravityScale);
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Player::~Player()
{
	delete m_gravity;
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
	auto state = m_gamePad->Get(m_gamePadNum);

	//���x��ݒ�
	//�y���͍��W�n�̊֘A�Ń}�C�i�X���|����
	switch (m_stick)
	{
	case RIGHT://�E�X�e�B�b�N
		m_spd->m_x = state.thumbSticks.rightX;	
		m_spd->m_z = -(state.thumbSticks.rightY);
		break;

	case LEFT://���X�e�B�b�N
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
	auto state = m_gamePad->Get(m_gamePadNum);

	//�{�^����������Ă��邩�ǂ���
	bool isPushed = false;

	//�X�e�B�b�N�ƑΉ�����{�^���Ŕ�����Ƃ�
	switch (m_stick)
	{
	case RIGHT://�E�X�e�B�b�N
		isPushed = state.IsRightShoulderPressed();
		break;

	case LEFT://���X�e�B�b�N
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

