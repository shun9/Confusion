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
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_state[i] = m_gamePad->GetState(i);
	}
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�Q�[���p�b�h�̏�Ԃ�Ԃ�
//�b����  :�Ȃ�(void)
//�b�߂�l:�Q�[���p�b�h�̏�Ԃ�Ԃ�(DirectX::GamePad::State)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
DirectX::GamePad::State GamePadManager::Get(int gamePadNum)
{ 
	return m_state[gamePadNum]; 
}


/*--�ȉ��B��--*/
//�R���X�g���N�^���f�X�g���N�^
GamePadManager::GamePadManager()
{

	m_gamePad = std::make_unique<DirectX::GamePad>();
	m_state = new DirectX::GamePad::State[Player::MAX_PLAYER];
}


GamePadManager::~GamePadManager() 
{
	delete[] m_state;
}
