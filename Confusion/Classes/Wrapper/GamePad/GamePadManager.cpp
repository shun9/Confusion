//************************************************/
//* @file  :GamePadManeger.cpp
//* @brief :�Q�[���p�b�h�̏�ԊǗ��p���b�v�N���X
//* @date  :2017/04/22
//* @author:S.Katou
//************************************************/
#include "GamePadManager.h"

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�C���X�^���X�̐����@�擾
//�b����  :�Ȃ�(void)
//�b�߂�l:�C���X�^���X(Key*)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
GamePadManager* GamePadManager::GetInstance()
{
	static GamePadManager gamePad;

	return &gamePad;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�Q�[���p�b�h�̏�Ԃ��X�V
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void GamePadManager::Update()
{
	m_state1 = m_gamePad->GetState(0);
	m_state2 = m_gamePad->GetState(1);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�Q�[���p�b�h�̏�Ԃ�Ԃ�
//�b����  :�Ȃ�(int)
//�b�߂�l:�Q�[���p�b�h�̏�Ԃ�Ԃ�(DirectX::GamePad::State)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
DirectX::GamePad::State GamePadManager::Get(int gamePadNum)
{ 
	switch (gamePadNum)
	{
	case 0:
		return m_state1;
	case 1:
		return m_state2;

	default:
		break;
	}
	return m_state1; 
}


/*--�ȉ��B��--*/
//�R���X�g���N�^���f�X�g���N�^
GamePadManager::GamePadManager()
{
	m_gamePad = std::make_unique<DirectX::GamePad>();
	m_state1 = m_gamePad->GetState(0);
	m_state2 = m_gamePad->GetState(1);
}


GamePadManager::~GamePadManager() 
{
}
