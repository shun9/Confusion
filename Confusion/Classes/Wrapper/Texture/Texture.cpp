//************************************************/
//* @file  :Texture.cpp
//* @brief :�摜�`��p�N���X
//* @date  :2017/04/18
//* @author:S.Katou
//************************************************/
#include "Texture.h"
#include <SimpleMath.h>

using namespace ShunLib;

// �f�o�C�X
Microsoft::WRL::ComPtr<ID3D11Device>Texture::m_device;

//�f�o�C�X�R���e�L�X�g
Microsoft::WRL::ComPtr<ID3D11DeviceContext>Texture::m_context;


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�o�C�X�̐ݒ�
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Texture::SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
{
	m_device = device;
	m_context = context;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t*)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Texture::Texture(const wchar_t* texture)
{
	//�e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(m_device.Get(), texture, nullptr, m_texture.ReleaseAndGetAddressOf());

	//�X�v���C�g�o�b�`�쐬
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context.Get());

	//�X�e�[�g�쐬
	m_state = std::make_unique<DirectX::CommonStates>(m_device.Get());

	//�v���~�e�B�u�o�b�`�쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(m_context.Get());

	//�A���t�@�G�t�F�N�g�쐬
	m_alphaTestEffect = std::make_unique<DirectX::AlphaTestEffect>(m_device.Get());
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_alphaTestEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//�C���v�b�g���C�A�E�g�쐬
	m_device->CreateInputLayout(DirectX::VertexPositionTexture::InputElements,
							    DirectX::VertexPositionTexture::InputElementCount,
								shaderByteCode,
								byteCodeLength,
								m_input.GetAddressOf());
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Texture::~Texture()
{

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :���W�w  (float)
//�b����  :���W�x  (float)
//�b����  :�g�嗦  (float)
//�b����  :�`���`(float)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Texture::Draw(float x, float y, float scale,const RECT* rect)
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
void ShunLib::Texture::Draw(const Matrix& world, const Matrix& view, const Matrix& proj, const Vec3& color, float alpha)
{
	//�e�N�X�`����ݒ�
	m_alphaTestEffect->SetTexture(m_texture.Get());

	//�e��s���ݒ�
	m_alphaTestEffect->SetWorld(world.GetDirectMatrix());
	m_alphaTestEffect->SetView(view.GetDirectMatrix());
	m_alphaTestEffect->SetProjection(proj.GetDirectMatrix());
	m_alphaTestEffect->SetColorAndAlpha(DirectX::SimpleMath::Color(color.m_x,color.m_y,color.m_z,alpha));

	//�`��ݒ�
	m_context->OMSetBlendState(m_state->AlphaBlend(), nullptr, 0xFFFFFFFF);
	m_context->OMSetDepthStencilState(m_state->DepthNone(), 0);
	m_context->RSSetState(m_state->CullNone());


	m_alphaTestEffect->Apply(m_context.Get());
	m_context->IASetInputLayout(m_input.Get());

	//�`��p���W
	DirectX::VertexPositionTexture vertexes[4] =
	{
		{ DirectX::SimpleMath::Vector3(-0.5f, 0.0f, 0.5f),DirectX::SimpleMath::Vector2(0.0f,0.0f) },
		{ DirectX::SimpleMath::Vector3( 0.5f, 0.0f, 0.5f),DirectX::SimpleMath::Vector2(1.0f,0.0f) },
		{ DirectX::SimpleMath::Vector3( 0.5f, 0.0f,-0.5f),DirectX::SimpleMath::Vector2(1.0f,1.0f) },
		{ DirectX::SimpleMath::Vector3(-0.5f, 0.0f,-0.5f),DirectX::SimpleMath::Vector2(0.0f,1.0f) },
	};

	uint16_t indexes[6] = { 0,1,2,2,3,0 };

	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indexes, 6, vertexes, 4);
	m_primitiveBatch->End();
}
