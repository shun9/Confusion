#include "Model.h"
#include <SimpleMath.h>
#include "../Matrix/Matrix.h"

using namespace ShunLib;

//�f�o�C�X�֘A
Microsoft::WRL::ComPtr<ID3D11Device> Model::m_device;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Model::m_context;

//�G�t�F�N�g�f�[�^
std::unique_ptr<DirectX::EffectFactory> Model::m_effect;
std::shared_ptr<DirectX::CommonStates> Model::m_state;


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�o�C�X�̐ݒ�
//�b����  :�f�o�C�X
//�b����  :�f�o�C�X�R���e�L�X�g
//�b����  :�X�e�[�g
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void ShunLib::Model::SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device, 
							   Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
							   std::shared_ptr<DirectX::CommonStates> state)
{
	m_device  = device;
	m_context = context;
	m_state   = state;
	m_effect  = std::make_unique<DirectX::EffectFactory>(m_device.Get());
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�I������
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void ShunLib::Model::Release()
{
	m_effect->ReleaseCache();
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�t�@�C���w��R���X�g���N�^	
//�b����  :cmo�t�@�C���̖��O(wchar_t[])
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Model::Model(const wchar_t cmo[])
{
	m_model = DirectX::Model::CreateFromCMO(m_device.Get(),cmo, *m_effect);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Model::~Model()
{
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
	m_model->Draw(m_context.Get() , *m_state, w, v, p);
}
