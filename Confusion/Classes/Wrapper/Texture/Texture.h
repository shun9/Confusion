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

namespace ShunLib
{
	class Texture
	{
		/*--静的変数--*/
	public:
		// デバイス
		static Microsoft::WRL::ComPtr<ID3D11Device> m_device;
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;

		//スプライトバッチ
		static std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		static std::shared_ptr<DirectX::CommonStates> m_state;


		/*--静的関数--*/
	public:
		//スプライトバッチの設定
		static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
							  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
							  std::shared_ptr<DirectX::CommonStates> state);

		/*--メンバ変数--*/
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;


		/*--メンバ関数--*/
	public:
		Texture(const wchar_t* texture);
		~Texture();

		//描画
		void Draw(float x, float y, float scale = 1.0f, const RECT* rect = nullptr);
	};
}