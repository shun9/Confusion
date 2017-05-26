//************************************************/
//* @file  :Texture.h
//* @brief :�摜�`��p�N���X
//* @date  :2017/04/18
//* @author:S.Katou
//************************************************/
#pragma once
#include <SpriteBatch.h>
#include <wrl.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>

#include "../Matrix/Matrix.h"

namespace ShunLib
{
	class Texture
	{
		/*--�ÓI�ϐ�--*/
	private:
		// �f�o�C�X
		static Microsoft::WRL::ComPtr<ID3D11Device>m_device;

		//�f�o�C�X�R���e�L�X�g
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext>m_context;

		/*--�ÓI�֐�--*/
	public:
		//�f�o�C�X�̐ݒ�
		static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
							  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);

		/*--�����o�ϐ�--*/
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

		//�X�v���C�g�o�b�`
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

		//�X�e�[�g�쐬
		std::unique_ptr<DirectX::CommonStates> m_state;

		//�G�t�F�N�g
		std::unique_ptr<DirectX::AlphaTestEffect> m_alphaTestEffect;

		//�v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;

		//�C���v�b�g���C�A�E�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_input;


		/*--�����o�֐�--*/
	public:
		Texture(const wchar_t* texture);
		~Texture();

		//�`��
		void Draw(float x, float y, float scale = 1.0f,const RECT* rect = nullptr);
		void Draw(const Matrix& world, const Matrix& view, const Matrix& proj, const Vec3& color=Vec3(1.0f,1.0f,1.0f), float alpha = 1.0f);
	};
}