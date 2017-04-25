//************************************************/
//* @file  :Texture.cpp
//* @brief :�摜�`��p�N���X
//* @date  :2017/04/18
//* @author:S.Katou
//************************************************/
#include "Texture.h"

using namespace ShunLib;

//�f�o�C�X
Microsoft::WRL::ComPtr<ID3D11Device> Texture::m_device;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Texture::m_context;

//�X�v���C�g�o�b�`
std::unique_ptr<DirectX::SpriteBatch> Texture::m_spriteBatch;

//�X�e�[�g
std::shared_ptr<DirectX::CommonStates> Texture::m_state;

//�G�t�F�N�g
std::unique_ptr<DirectX::AlphaTestEffect> Texture::m_alphaTestEffect;

//�v���~�e�B�u�o�b�`
std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> Texture::m_primitiveBatch;

//�C���v�b�g���C�A�E�g
Microsoft::WRL::ComPtr<ID3D11InputLayout> Texture::m_input;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�o�C�X�̐ݒ�
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Texture::SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
					    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
						std::shared_ptr<DirectX::CommonStates> state)
{
	m_device = device;
	m_context = context;
	m_state = state;
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context.Get());

	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(m_context.Get());

	m_alphaTestEffect = std::make_unique<DirectX::AlphaTestEffect>(m_device.Get());

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_alphaTestEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	m_device->CreateInputLayout(DirectX::VertexPositionTexture::InputElements,
							    DirectX::VertexPositionTexture::InputElementCount,
								shaderByteCode,
								byteCodeLength,
								m_input.GetAddressOf());

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t*)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Texture::Texture(const wchar_t* texture)
{
	DirectX::CreateWICTextureFromFile(m_device.Get(), texture, nullptr, m_texture.ReleaseAndGetAddressOf());
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Texture::~Texture()
{
	m_texture.Reset();
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�I������
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Texture::Release()
{
	m_spriteBatch.release();
	m_primitiveBatch.release();
	m_alphaTestEffect.release();
	m_input.Reset();
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :���W�w  (float)
//�b����  :���W�x  (float)
//�b����  :�g�嗦  (float)
//�b����  :�`���`(float)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Texture::Draw(float x, float y, float scale, const RECT* rect)
{
	using namespace DirectX;

	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_state->NonPremultiplied());

	m_spriteBatch->Draw(m_texture.Get(), XMFLOAT2(x, y), rect, Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(scale, scale));

	m_spriteBatch->End();

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R�c�`�揈��
//�b����  :���[���h(Matrix)
//�b����  :�r���[�@(Matrix)
//�b����  :�ˉe�s��(Matrix)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void ShunLib::Texture::Draw(const Matrix& world, const Matrix& view, const Matrix& proj)
{
	m_alphaTestEffect->SetTexture(m_texture.Get());

	m_alphaTestEffect->SetWorld(world.GetDirectMatrix());
	m_alphaTestEffect->SetView(view.GetDirectMatrix());
	m_alphaTestEffect->SetProjection(proj.GetDirectMatrix());


	m_context->OMSetBlendState(m_state->Opaque(), nullptr, 0xFFFFFFFF);
	m_context->OMSetDepthStencilState(m_state->DepthNone(), 0);
	m_context->RSSetState(m_state->CullNone());

	m_alphaTestEffect->Apply(m_context.Get());
	m_context->IASetInputLayout(m_input.Get());

	DirectX::VertexPositionTexture vertexes[4] =
	{
		{ DirectX::SimpleMath::Vector3(-0.5f, 0.0f,0.5f),DirectX::SimpleMath::Vector2(0.0f,0.0f) },
		{ DirectX::SimpleMath::Vector3(0.5f, 0.0f,0.5f),DirectX::SimpleMath::Vector2(1.0f,0.0f) },
		{ DirectX::SimpleMath::Vector3(0.5f,0.0f,-0.5f),DirectX::SimpleMath::Vector2(1.0f,1.0f) },
		{ DirectX::SimpleMath::Vector3(-0.5f,0.0f,-0.5f),DirectX::SimpleMath::Vector2(0.0f,1.0f) },
	};

	uint16_t indexes[6] = { 0,1,2,2,3,0 };

	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indexes, 6, vertexes, 4);
	m_primitiveBatch->End();


}
