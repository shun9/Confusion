//************************************************/
//* @file  :Texture.cpp
//* @brief :画像描画用クラス
//* @date  :2017/04/18
//* @author:S.Katou
//************************************************/
#include "Texture.h"

using namespace ShunLib;

//デバイス
ID3D11Device* Texture::m_device;
ID3D11DeviceContext* Texture::m_context;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デバイスの設定
//＋ーーーーーーーーーーーーーー＋
void Texture::SetDevice(ID3D11Device* device,
					    ID3D11DeviceContext* context){
	m_device = device;
	m_context = context;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//｜引数  :画像のパス(wchar_t*)
//＋ーーーーーーーーーーーーーー＋
Texture::Texture(const wchar_t* texture)
{
	//テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(m_device, texture, nullptr, m_texture.ReleaseAndGetAddressOf());
	
	//スプライトバッチ作成
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context);

	//ステート作成
	m_state = std::make_unique<DirectX::CommonStates>(m_device);

	//プリミティブバッチ作成
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(m_context);

	//アルファエフェクト作成
	m_alphaTestEffect = std::make_unique<DirectX::AlphaTestEffect>(m_device);
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_alphaTestEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//インプットレイアウト作成
	m_device->CreateInputLayout(DirectX::VertexPositionTexture::InputElements,
		DirectX::VertexPositionTexture::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		m_input.GetAddressOf());
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Texture::~Texture()
{
	m_texture.Reset();
	m_spriteBatch.release();
	m_input.Reset();
	m_alphaTestEffect.reset();
	m_primitiveBatch.reset();
	m_state.reset();
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

	m_spriteBatch->Draw(m_texture.Get(), XMFLOAT2(x, y), rect, Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(scale, scale));

	m_spriteBatch->End();

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :３Ｄ描画処理
//｜引数  :ワールド(Matrix)
//｜引数  :ビュー　(Matrix)
//｜引数  :射影行列(Matrix)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void ShunLib::Texture::Draw(const Matrix& world, const Matrix& view, const Matrix& proj)
{
	m_alphaTestEffect->SetTexture(m_texture.Get());

	m_alphaTestEffect->SetWorld(world.GetDirectMatrix());
	m_alphaTestEffect->SetView(view.GetDirectMatrix());
	m_alphaTestEffect->SetProjection(proj.GetDirectMatrix());


	m_context->OMSetBlendState(m_state->Opaque(), nullptr, 0xFFFFFFFF);
	m_context->OMSetDepthStencilState(m_state->DepthNone(), 0);
	m_context->RSSetState(m_state->CullNone());


	m_alphaTestEffect->Apply(m_context);
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
