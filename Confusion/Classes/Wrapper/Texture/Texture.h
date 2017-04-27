//************************************************/
//* @file  :Texture.h
//* @brief :画像描画用クラス
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
		/*--静的変数--*/
	private:
		// デバイス
		static ID3D11Device* m_device;
		static ID3D11DeviceContext* m_context;

		/*--静的関数--*/
	public:
		//デバイスの設定
		static void SetDevice(ID3D11Device* device,
							  ID3D11DeviceContext* context);


		/*--メンバ変数--*/
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

		//スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		
		//ステート作成
		std::unique_ptr<DirectX::CommonStates> m_state;

		//エフェクト
		std::unique_ptr<DirectX::AlphaTestEffect> m_alphaTestEffect;
	
		//プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;

		//インプットレイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_input;


		/*--メンバ関数--*/
	public:
		Texture(const wchar_t* texture);
		~Texture();

		//描画
		void Draw(float x, float y, float scale = 1.0f, const RECT* rect = nullptr);
		void Draw(const Matrix& world, const Matrix& view, const Matrix& proj);
	};
}