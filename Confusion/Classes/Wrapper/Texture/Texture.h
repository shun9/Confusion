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
	public:
		// �f�o�C�X
		static Microsoft::WRL::ComPtr<ID3D11Device> m_device;
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;

		//�X�v���C�g�o�b�`
		static std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		static std::shared_ptr<DirectX::CommonStates> m_state;

		//�G�t�F�N�g
		static 	std::unique_ptr<DirectX::AlphaTestEffect> m_alphaTestEffect;

		//�v���~�e�B�u�o�b�`
		static std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;

		//�C���v�b�g���C�A�E�g
		static Microsoft::WRL::ComPtr<ID3D11InputLayout> m_input;

		/*--�ÓI�֐�--*/
	public:
		//�X�v���C�g�o�b�`�̐ݒ�
		static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
							  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
							  std::shared_ptr<DirectX::CommonStates> state);

		/*--�����o�ϐ�--*/
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;


		/*--�����o�֐�--*/
	public:
		Texture(const wchar_t* texture);
		~Texture();

		//�`��
		void Draw(float x, float y, float scale = 1.0f, const RECT* rect = nullptr);
		void Draw(const Matrix& world, const Matrix& view, const Matrix& proj);
	};
}