//************************************************/
//* @file  :GamePadManeger.h
//* @brief :�Q�[���p�b�h�̏�ԊǗ��p���b�v�N���X
//* @date  :2017/04/22
//* @author:S.Katou
//************************************************/
#pragma once
#include <GamePad.h>
#include "../../Player/Player.h"

class GamePadManager
{
public:
	static GamePadManager* GamePadManager::GetInstance();


private:
	//�Q�[���p�b�h
	std::unique_ptr<DirectX::GamePad>m_gamePad;

	//�Q�[���p�b�h�̏��
	DirectX::GamePad::State* m_state;

public:
	//�X�V����
	void Update();

	//��Ԃ�Ԃ�
	DirectX::GamePad::State Get(int gamePadNum);


	//�ݒ�֘A�i�悭�킩��Ȃ����ǕK�v�j
	void Suspend() { m_gamePad->Suspend(); }
	void Resume() { m_gamePad->Resume(); }

	/*--�B��--*/
private:
	//�R���X�g���N�^���f�X�g���N�^
	GamePadManager();
	~GamePadManager();
};
