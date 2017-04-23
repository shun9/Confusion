//************************************************/
//* @file  :Gravity.cpp
//* @brief :�v���C���[��������d�͂̃N���X
//* @date  :2017/04/23
//* @author:S.Katou
//************************************************/
#include "Gravity.h"

using namespace ShunLib;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t)
//�b����  :�����ʒu(Vec3)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Gravity::Gravity(const wchar_t* texture, const Vec3 & pos)
	: m_texture(new Texture(texture)) //delete -> ~Gravity
	, m_pos(pos)
	, m_scale(1.0f)
	, m_angle(360.0f)
{

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Gravity::~Gravity()
{
	//new -> Gravity
	delete m_texture;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Gravity::Update()
{
	//���v���
	m_angle -= 2.0f;

	if (m_angle <= 0.0f)
	{
		m_angle = 360.0f;
	}
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`��
//�b����  :�r���[�s��(Matrix)
//�b����  :�ˉe�s��(Matrix)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Gravity::Draw(Matrix view, Matrix proj)
{
	Matrix world;
	world = Matrix::CreateScale(m_scale)
		  * Matrix::CreateRotationY(m_angle)
    	  * Matrix::CreateTranslation(m_pos);

	m_texture->Draw(world, view, proj);
}
