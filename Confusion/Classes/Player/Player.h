//************************************************/
//* @file  :Player.h
//* @brief :�v���C���[�̃w�b�_�[
//* @date  :2017/04/22
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Object/Object.h"
#include "../Gravity/Gravity.h"

class GamePadManager;


//�萔�@����
enum DIRECTION
{
	TOP,
	BOTTOM,
	RIGHT,
	LEFT,
};


//�v���C���[�N���X
class Player :public Object
{
	/*--�ÓI�ϐ�--*/
public:
	//�v���C���[�ő吔
	static const int MAX_PLAYER;


	/*--�����o�ϐ�--*/
private:
	//�Q�[���p�b�h
	GamePadManager* m_gamePad;
	
	//�Ή�����Q�[���p�b�h�̔ԍ�
	int m_gamePadNum;

	//�ړ��p�ɑΉ�����X�e�B�b�N�i�E or ���j
	DIRECTION m_stick;

	//�d��
	Gravity* m_gravity;
	float m_gravityScale;


	/*--�����o�֐�--*/
public:
	Player(const wchar_t* model,
		   ShunLib::Vec3 pos,
		   int gamePadNum,
		   DIRECTION stick);
	~Player();

	//�X�V����
	void Update()override;

	//�d�͂̕`��
	void DrawGravity(const ShunLib::Matrix& view,
				  	 const ShunLib::Matrix& proj);

private:
	//�ړ����x�̍X�V
	void UpdateSpd();

	//�d�͊֘A�̍X�V
	void UpdateGravity();

	//�d�͂̊g�嗦�̍X�V
	void UpdateGravityScale();
};
