//************************************************/
//* @file  :Player.cpp
//* @brief :�v���C���[�̃\�[���t�@�C��
//* @date  :2017/04/22
//* @author:S.Katou
//************************************************/
#include "Player.h"
#include "../Wrapper/GamePad/GamePadManager.h"

//�v���C���[�ő吔
const int Player::MAX_PLAYER = 2;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t*)
//�b����  :�������W	 (ShunLib::Vec3)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Player::Player(const wchar_t* model, ShunLib::Vec3 pos, int gamePadNum,DIRECTION stick)
	:Object(model, pos)
	,m_gamePadNum(gamePadNum)
	,m_stick(stick)
{
	m_gamePad = GamePadManager::GetInstance();

	//delete -> ~Player
	m_gravity = new Gravity(L"Effect\\gravity.png");
	m_gravity->Scale(0.1f);
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Player::~Player()
{
	//new -> Player
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
	*m_pos = *m_pos + *m_spd;


	//�d�͈ʒu���ړ�
	m_gravity->Pos(m_pos->m_x,-1.0f,m_pos->m_z);

	//�d�͍X�V
	m_gravity->Update();
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�d�͂̕`��
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Player::DrawGravity(const ShunLib::Matrix & view, const ShunLib::Matrix & proj)
{
	m_gravity->Draw(view, proj);
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
		m_spd->m_x = state.thumbSticks.rightX / 10.0f;	
		m_spd->m_z = -(state.thumbSticks.rightY / 10.0f);
		break;

	case LEFT://���X�e�B�b�N
		m_spd->m_x = state.thumbSticks.leftX / 10.0f;
		m_spd->m_z = -(state.thumbSticks.leftY / 10.0f);
		break;

	default://����ȊO�͍�
		m_spd->m_x = state.thumbSticks.leftX / 10.0f;
		m_spd->m_z = -(state.thumbSticks.leftY / 10.0f);
		break;
	}
}

