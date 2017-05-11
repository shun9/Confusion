//************************************************/
//* @file  :HPGauge.cpp
//* @brief :�q�b�g�|�C���g�N���X
//* @date  :2017/05/11
//* @author:S.Katou
//************************************************/
#include "HPGauge.h"

HPGauge::HPGauge(int max, ShunLib::Vec3 pos, ShunLib::Vec3 scale, ShunLib::Vec3 rotate)
	:MAX_HP(max)
	, m_hp(max)
{
	using namespace ShunLib;

	//delete -> ~Player
	m_red    = new ShunLib::Texture(L"Images\\GaugeRed.png");
	m_green  = new ShunLib::Texture(L"Images\\GaugeGreen.png");
	m_pos    = new Vec3(pos);
	m_scale  = new Vec3(scale);
	m_rotate = new Vec3(rotate);

}

HPGauge::~HPGauge()
{
	delete m_red;
	delete m_green;
	delete m_pos;
	delete m_scale;
	delete m_rotate;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :HP�Q�[�W�̕`��
//�b����  :�r���[�s��		   (ShunLib::Matrix)
//�b����  :�v���W�F�N�V�����s��(ShunLib::Matrix)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void HPGauge::Draw(const ShunLib::Matrix & view, const ShunLib::Matrix & proj)
{
	using namespace ShunLib;

	//�ԗp
	Matrix scale  = Matrix::CreateScale(*m_scale);
	Matrix rotate = Matrix::CreateRotationZ(m_rotate->m_z)
				  * Matrix::CreateRotationX(m_rotate->m_x)
				  * Matrix::CreateRotationY(m_rotate->m_y);
	Matrix trans  = Matrix::CreateTranslation(Vec3(m_pos->m_x, 
												   0.0f, 
												   m_pos->m_z));

	//�Ηp
	Matrix scale2  = Matrix::CreateScale(Vec3(m_scale->m_x*m_hp / MAX_HP, 
											  m_scale->m_y, 
											  m_scale->m_z));
	Matrix trans2  = Matrix::CreateTranslation(Vec3(m_pos->m_x - ((1.0f - m_hp / (float)MAX_HP)*(m_scale->m_x/2)),
													0.0f, 
													m_pos->m_z));
	//���Z
	Matrix worldRed = scale*rotate*trans;
	Matrix worldGreen = scale2*rotate*trans2;

	//�`��
	m_red->Draw(worldRed, view, proj);
	m_green->Draw(worldGreen, view, proj);

}
