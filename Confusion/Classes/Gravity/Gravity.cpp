//************************************************/
//* @file  :Gravity.cpp
//* @brief :�v���C���[��������d�͂̃N���X
//* @date  :2017/04/23
//* @author:S.Katou
//************************************************/
#include "Gravity.h"

using namespace ShunLib;
const float Gravity::POWER = 0.07f;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t)
//�b����  :�����ʒu(Vec3)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Gravity::Gravity(const wchar_t* texture, const Vec3 & pos)
	: m_texture(new Texture(texture)) //delete -> ~Gravity
	, m_pos(pos)
	, m_radius(1.0f)
	, m_angle(360.0f)
{

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Gravity::~Gravity()
{
	delete m_texture;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Gravity::Update()
{
	//���v���ŉ�]������
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
	world = Matrix::CreateScale(m_radius*2)
		  * Matrix::CreateRotationY(m_angle)
    	  * Matrix::CreateTranslation(m_pos);

	m_texture->Draw(world, view, proj);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�Ώۂ������񂹂�
//�b����  :�Ώۂ̈ʒu(Vec3*)����������
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Gravity::Attract(ShunLib::Vec3* objPos)
{
	using namespace ShunLib;

	//�d�͂��������Ă��Ȃ���ΏI��
	if (m_radius <= 0.0f)
	{
		return;
	}

	float x = objPos->m_x - m_pos.m_x;
	float z = objPos->m_z - m_pos.m_z;

	Vec3 vec = { x, 0.0f, z };
	vec.Normalize();
	objPos->m_x -= vec.m_x*POWER;
	objPos->m_z -= vec.m_z*POWER;
}
