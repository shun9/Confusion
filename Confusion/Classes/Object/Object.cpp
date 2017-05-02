//************************************************/
//* @file  :Object.cpp
//* @brief :�I�u�W�F�N�g�̊��N���X
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#include "Object.h"
#include "../Conversion/Conversion.h"

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t*)
//�b����  :�������W	 (ShunLib::Vec3)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Object::Object(const wchar_t* model, ShunLib::Vec3 pos, ShunLib::Vec3 spd)
	: m_angle(0.0f)
{
	using namespace ShunLib;

	//delete -> ~Object
	m_model = new Model(model);
	m_pos   = new Vec3(pos);
	m_spd   = new Vec3(spd);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Object::~Object()
{
	delete m_model;
	delete m_pos;
	delete m_spd;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`��
//�b����  :���[���h�s��		   (ShunLib::Matrix)
//�b����  :�r���[�s��		   (ShunLib::Matrix)
//�b����  :�v���W�F�N�V�����s��(ShunLib::Matrix)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Object::Draw(const ShunLib::Matrix& view, const ShunLib::Matrix& proj)
{
	using namespace ShunLib;

	//�����Ă���������v�Z����
	CalculateDirection();

	Matrix world = Matrix::CreateRotationY(m_angle) * Matrix::CreateTranslation(*m_pos);
	m_model->Draw(world, view, proj);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�����Ă���������v�Z����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Object::CalculateDirection()
{
	//�����Ă��Ȃ���Όv�Z���Ȃ�
	if (m_spd->m_x == 0.0f&&m_spd->m_y==0.0f&&m_spd->m_z==0.0f)
	{
		return;
	}

	m_spd->Normalize();

	float rot = ShunLib::ToAngle(std::atan2(m_spd->m_z, m_spd->m_x)) - 90.0f;

	m_angle = rot;
}
