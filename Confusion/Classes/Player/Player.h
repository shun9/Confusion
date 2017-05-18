//************************************************/
//* @file  :Player.h
//* @brief :�v���C���[�N���X
//* @date  :2017/05/15
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Object/Object.h"
#include "../Gravity/Gravity.h"
#include "../Wrapper/ConstantNumber/ConstantNumber.h"
#include "../Object/HPGauge.h"

class GamePadManager;

//�v���C���[�N���X
class Player :public Object
{
	/*--�ÓI�ϐ�--*/
private:
	//���x�{��
	static const float SPD_MAGNIFICATION;
	static const int MAX_HP;

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
	ShunLib::DIRECTION_2D m_stick;

	//�d��
	Gravity* m_gravity;
	float m_gravityScale;

	//�q�b�g�|�C���g
	HPGauge* m_hpGauge;
	int m_hp;

	//���G����
	int m_invincibleTime;

	/*--���J�֐�--*/
public:
	Player(const wchar_t* model,
		   ShunLib::Vec3 pos,
		   int gamePadNum,
		   ShunLib::DIRECTION_2D stick);
	~Player();

	//�X�V����
	void Update()override;

	//�`�揈��
	virtual void Draw(const ShunLib::Matrix& view,
					  const ShunLib::Matrix& proj);

	//�d�͂̕`��(�`�揇�̊֌W�ŕ�;����)
	void DrawGravity(const ShunLib::Matrix& view, const ShunLib::Matrix& proj) { m_gravity->Draw(view, proj); }

	//�d�͂̏���Ԃ�
	Gravity* GetGravity() { return m_gravity; }
	
	//�_���[�W���󂯂�
	void TakeDamage(int damage) { m_hp -= damage; }

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

	//�g�o�Q�[�W�`��
	void DrawHpGauge(const ShunLib::Matrix& view, const ShunLib::Matrix& proj);
};
