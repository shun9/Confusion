//************************************************/
//* @file  :Model.h
//* @brief :���f���p�̃��b�v�N���X
//* @date  :2017/02/21
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>
#include "../Matrix/Matrix.h"

namespace ShunLib
{
	class Model
	{
		/*--�ÓI�ϐ�--*/
	private:
		// �f�o�C�X
		static Microsoft::WRL::ComPtr<ID3D11Device> m_device;

		//�f�o�C�X�R���e�L�X�g
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;
		
		//�G�t�F�N�g�f�[�^
		static std::unique_ptr<DirectX::EffectFactory> m_effect;
	
		//�X�e�[�g
		static std::shared_ptr<DirectX::CommonStates> m_state;


		/*--�ÓI�֐�--*/
	public:
		//�f�o�C�X�̐ݒ�
		static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
							  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
							  std::shared_ptr<DirectX::CommonStates> state);
		//���f���S�̂̏I������
		static void Release();

		/*--�����o�ϐ�--*/
	private:
		//���f���f�[�^
		std::unique_ptr<DirectX::Model> m_model;


		/*--�����o�֐�--*/
	public:

		//�t�@�C���w��R���X�g���N�^
		Model(const wchar_t cmo[]);

		//�f�X�g���N�^
		~Model();

		//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
		//�b�@�\  :���f���̕`��
		//�b����  :���[���h�s��	(Matrix)
		//�b����  :�r���[�s��	(Matrix)
		//�b����  :�ˉe�s��		(Matrix)
		//�b�߂�l:�Ȃ�(void)	
		//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
		void Draw(const Matrix& world,
				  const Matrix& view,
				  const Matrix& proj)
		{
			DirectX::SimpleMath::Matrix w = world.GetDirectMatrix();	// ���[���h
			DirectX::SimpleMath::Matrix v = view.GetDirectMatrix();		// �r���[
			DirectX::SimpleMath::Matrix p = proj.GetDirectMatrix();		// �v���W�F�N�V����

			// �`��		 �R���e�L�X�g,�X�e�[�g,���[���h,�r���[,�v���W�F�N�V����
			m_model->Draw(m_context.Get(), *m_state, w, v, p);
		}

	};
}