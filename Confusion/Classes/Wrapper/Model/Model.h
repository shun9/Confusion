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
		static Microsoft::WRL::ComPtr<ID3D11Device>m_device;

		//�f�o�C�X�R���e�L�X�g
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext>m_context;

	//	/*--�ÓI�֐�--*/
	public:
		//�f�o�C�X�̐ݒ�
		static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
							  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);

		/*--�����o�ϐ�--*/
	private:
		//���f���f�[�^
		std::unique_ptr<DirectX::Model> m_model;

		//�G�t�F�N�g�f�[�^
		std::unique_ptr<DirectX::EffectFactory> m_effect;

		//�X�e�[�g
		std::unique_ptr<DirectX::CommonStates> m_state;

		/*--�����o�֐�--*/
	public:

		//�t�@�C���w��R���X�g���N�^
		Model(const wchar_t cmo[]);

		//�f�X�g���N�^
		~Model();

		//�b�`��
		void Draw(const Matrix& world,
				  const Matrix& view,
				  const Matrix& proj);
	};
}