//************************************************/
//* @file  :Player.h
//* @brief :�v���C���[�̃w�b�_�[
//* @date  :2017/04/28
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
private:
	//���x�{��
	static const float SPD_MAGNIFICATION;

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

	//�q�b�g�|�C���g
	int m_hp;
	
	//���G����
	int m_invincibleTime;

	/*--���J�֐�--*/
public:
	Player(const wchar_t* model,
		   ShunLib::Vec3 pos,
		   int gamePadNum,
		   DIRECTION stick);
	~Player();

	//�X�V����
	void Update()override;

	//�d�͂̕`��
	void DrawGravity(const ShunLib::Matrix& view, const ShunLib::Matrix& proj)
	{	m_gravity->Draw(view, proj);	}

	//�d�͂̏���Ԃ�
	Gravity* GetGravity() { return m_gravity; }
	
	//�_���[�W���󂯂�
	void TakeDamage(int damage) {m_hp -= damage;}

	//�g�o
	int Hp() { return m_hp; }

	//���G����
	int InvincibleTime() { return m_invincibleTime; }
	void InvincibleTime(int time) { m_invincibleTime = time; }

	//�X�e�[�W�O�ɏo�Ȃ��悤�ɂ���
	void Clamp(float top,float bottom,float right,float left);

	/*--����J�֐�--*/
private:
	//�ړ����x�̍X�V
	void UpdateSpd();

	//�d�͊֘A�̍X�V
	void UpdateGravity();

	//�d�͂̊g�嗦�̍X�V
	void UpdateGravityScale();
};
