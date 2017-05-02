//************************************************/
//* @file  :Enemy.h
//* @brief :�G�̃w�b�_�[�t�@�C��
//* @date  :2017/05/01
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Object/Object.h"
#include "../Wrapper/Vec3/Vec3.h"

class Enemy : public Object
{
private:
	//���x�{��
	static const float SPD_MAGNIFICATION;

private:
	//����
	bool m_isDead;
	
	//��������
	int m_confusedTime;

	//�������Ă��邩�ǂ���
	bool m_isConfused;

	//�ŏ��̑��x
	ShunLib::Vec3 m_firstSpd;

public:
	Enemy(const wchar_t* model, 
		ShunLib::Vec3 pos = (0.0f, 0.0f, 0.0f),
		ShunLib::Vec3 spd=(0.0f,0.0f,0.0f));
	~Enemy();

	//�X�V
	void Update()override;

	//��������
	void Fluster();

	//�������Ă��邩�ǂ���
	bool IsConfused() { return m_isConfused; }
	
	//��
	void Dead() { m_isDead = true; }
	
	//�͈͊O�ɏo���玀
	void Dead(float top, float bottom, float right, float left);

	//����ł��邩�ǂ���
	bool IsDead() { return m_isDead; }
};
