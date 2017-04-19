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
	m_spriteBatch.reset();
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

	m_spriteBatch->Draw(m_texture.Get(), XMFLOAT2(x, y), rect, Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(scale,scale));

	m_spriteBatch->End();

}
