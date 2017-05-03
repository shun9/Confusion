//************************************************/
//* @file  :Effect.h
//* @brief :Effekseerを使用したエフェクト再生クラス
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <memory>
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>

namespace ShunLib
{
	class Effect
	{
		/*--静的変数--*/
	private:
		// デバイス
		static ID3D11Device* m_device;

		//デバイスコンテキスト
		static ID3D11DeviceContext* m_context;


		//	/*--静的関数--*/
	public:
		//デバイスの設定
		static void SetDevice(ID3D11Device* device,
			ID3D11DeviceContext* context);

		/*--メンバ変数--*/
	private:

		EffekseerRenderer::Renderer* renderer;
		Effekseer::Manager* manager;
		EffekseerSound::Sound* sound;
		Effekseer::Effect* effect;
		Effekseer::Handle handle;

		/*--メンバ関数--*/
	public:

		//ファイル指定コンストラクタ
		Effect(const wchar_t efk[]);

		//デストラクタ
		~Effect();
	};
}