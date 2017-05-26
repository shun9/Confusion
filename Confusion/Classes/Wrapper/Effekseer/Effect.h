//************************************************/
//* @file  :Effect.h
//* @brief :Effekseerを使用したエフェクト再生クラス
//* @date  :2017/05/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <memory>
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include "../Matrix/Matrix.h"

namespace ShunLib
{
	class Effect
	{
		/*--静的変数--*/
	private:
		// デバイス
		static Microsoft::WRL::ComPtr<ID3D11Device>m_device;

		//デバイスコンテキスト
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext>m_context;


		/*--静的関数--*/
	public:
		//デバイスの設定
		static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
							  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
		static void ResetDevice();

		/*--メンバ変数--*/
	private:
		EffekseerRenderer::Renderer* renderer;
		Effekseer::Manager* manager;
		Effekseer::Effect* effect;
		Effekseer::Handle handle;

		//エフェクトのフレーム数（時間）
		int m_flame;

		//フレームのカウント
		int m_flameCnt;

		//再生が終了したらtrue
		bool m_isEnded;

		//再生速度倍率
		float m_spd;

		/*--メンバ関数--*/
	public:

		//ファイル指定コンストラクタ
		Effect(const wchar_t efk[], int flame, int spriteNum = 32, bool isDrawFirst = false);

		//デストラクタ
		~Effect();

		void Draw(const ShunLib::Matrix& view,
				  const ShunLib::Matrix& proj);

		void DrawLoop(const ShunLib::Matrix& view,
					  const ShunLib::Matrix& proj);

		//描画の状態をリセットする
		void SetDraw(const ShunLib::Vec3 pos = ShunLib::Vec3::Zero)
		{
			handle = manager->Play(effect, pos.m_x,pos.m_y,pos.m_z);
			m_isEnded = false;
			m_flameCnt = 0;
		}

		//位置を設定
		void SetPos(const ShunLib::Vec3 pos)
		{
			//位置ベクトルコピー
			Effekseer::Vector3D e_pos = { pos.m_x,pos.m_y,pos.m_z };
			manager->SetLocation(handle, e_pos);
		}

		//拡大率を設定
		void SetScale(const ShunLib::Vec3 scale)
		{
			manager->SetScale(handle, scale.m_x, scale.m_y, scale.m_z);
		}

		//再生速度を設定
		void SetSpd(float spd)
		{
			m_spd = spd;
			manager->SetSpeed(handle, m_spd);
		}

		//傾きを設定
		void SetRotate(const ShunLib::Vec3 axis,float angle)
		{
			Effekseer::Vector3D e_axis = { axis.m_x,axis.m_y,axis.m_z };
			manager->SetRotation(handle, e_axis, angle);
		}

		//再生が終了したかどうか
		bool IsEnded() { return m_isEnded; }
	};
}