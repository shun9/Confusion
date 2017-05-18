#include "Model.h"
#include <SimpleMath.h>
#include "../Matrix/Matrix.h"

using namespace ShunLib;

//�f�o�C�X�֘A
ID3D11Device* Model::m_device;
ID3D11DeviceContext* Model::m_context;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�o�C�X�̐ݒ�
//�b����  :�f�o�C�X
//�b����  :�f�o�C�X�R���e�L�X�g
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void ShunLib::Model::SetDevice(ID3D11Device* device, 
							   ID3D11DeviceContext* context)
{
	m_device  = device;
	m_context = context;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�t�@�C���w��R���X�g���N�^	
//�b����  :cmo�t�@�C���̖��O(wchar_t[])
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Model::Model(const wchar_t cmo[])
{
	//�X�e�[�g�쐬
	m_state = std::make_unique<DirectX::CommonStates>(m_device);
	
	//�G�t�F�N�g�쐬
	m_effect = std::make_unique<DirectX::EffectFactory>(m_device);

	//�e�N�X�`���̏ꏊ���w��
	m_effect->SetDirectory(L"CModel");

	//���f���̍쐬
	m_model = DirectX::Model::CreateFromCMO(m_device,cmo, *m_effect);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Model::~Model()
{
	m_state.reset();
	m_effect.reset();
	m_model.reset();
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :���f���̕`��
//�b����  :���[���h�s��	(Matrix)
//�b����  :�r���[�s��	(Matrix)
//�b����  :�ˉe�s��		(Matrix)
//�b�߂�l:�Ȃ�(void)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Model::Draw(const Matrix& world,
				 const Matrix& view,
				 const Matrix& proj)
{
	DirectX::SimpleMath::Matrix w = world.GetDirectMatrix();	// ���[���h
	DirectX::SimpleMath::Matrix v = view.GetDirectMatrix();		// �r���[
	DirectX::SimpleMath::Matrix p = proj.GetDirectMatrix();		// �v���W�F�N�V����

	// �`��		 �R���e�L�X�g,�X�e�[�g,���[���h,�r���[,�v���W�F�N�V����
	m_model->Draw(m_context, *m_state, w, v, p);
}
