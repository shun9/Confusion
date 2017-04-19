//************************************************/
//* @file  :Texture.cpp
//* @brief :画像描画用クラス
//* @date  :2017/04/18
//* @author:S.Katou
//************************************************/
#include "Texture.h"

using namespace ShunLib;

//デバイス
Microsoft::WRL::ComPtr<ID3D11Device> Texture::m_device;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Texture::m_context;

//スプライトバッチ
std::unique_ptr<DirectX::SpriteBatch> Texture::m_spriteBatch;

//ステート
std::shared_ptr<DirectX::CommonStates> Texture::m_state;


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デバイスの設定
//＋ーーーーーーーーーーーーーー＋
void Texture::SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
					    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
						std::shared_ptr<DirectX::CommonStates> state)
{
	m_device = device;
	m_context = context;
	m_state = state;
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context.Get());
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//｜引数  :画像のパス(wchar_t*)
//＋ーーーーーーーーーーーーーー＋
Texture::Texture(const wchar_t* texture)
{
	DirectX::CreateWICTextureFromFile(m_device.Get(), texture, nullptr, m_texture.ReleaseAndGetAddressOf());
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Texture::~Texture()
{
	m_texture.Reset();
	m_spriteBatch.reset();
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :座標Ｘ  (float)
//｜引数  :座標Ｙ  (float)
//｜引数  :拡大率  (float)
//｜引数  :描画矩形(float)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Texture::Draw(float x, float y, float scale, const RECT* rect)
{
	using namespace DirectX;

	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_state->NonPremultiplied());

	m_spriteBatch->Draw(m_texture.Get(), XMFLOAT2(x, y), rect, Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(scale,scale));

	m_spriteBatch->End();

}
