//************************************************/
//* @file  :Object.cpp
//* @brief :�I�u�W�F�N�g�̊��N���X
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#include "Object.h"

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t*)
//�b����  :�������W	 (ShunLib::Vec3)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Object::Object(const wchar_t* model, ShunLib::Vec3 pos)
{
	using namespace ShunLib;

	//delete -> ~Object
	m_model = new Model(model);
	m_pos   = new Vec3(pos);
	m_spd   = new Vec3(0.0f, 0.0f, 0.0f);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Object::~Object()
{
	//new -> Object
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

	Matrix world = Matrix::CreateTranslation(*m_pos);
	m_model->Draw(world, view, proj);
}
