//************************************************/
//* @file  :Model.h
//* @brief :モデル用のラップクラス
//* @date  :2017/02/21
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>
#include "../Matrix/Matrix.h"

namespace ShunLib
{
	class Model
	{
		/*--静的変数--*/
	private:
		// デバイス
		static Microsoft::WRL::ComPtr<ID3D11Device>m_device;

		//デバイスコンテキスト
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext>m_context;

	//	/*--静的関数--*/
	public:
		//デバイスの設定
		static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
							  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);

		/*--メンバ変数--*/
	private:
		//モデルデータ
		std::unique_ptr<DirectX::Model> m_model;

		//エフェクトデータ
		std::unique_ptr<DirectX::EffectFactory> m_effect;

		//ステート
		std::unique_ptr<DirectX::CommonStates> m_state;

		/*--メンバ関数--*/
	public:

		//ファイル指定コンストラクタ
		Model(const wchar_t cmo[]);

		//デストラクタ
		~Model();

		//｜描画
		void Draw(const Matrix& world,
				  const Matrix& view,
				  const Matrix& proj);
	};
}