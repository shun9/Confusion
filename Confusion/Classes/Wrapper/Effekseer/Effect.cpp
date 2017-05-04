//************************************************/
//* @file  :Effect.cpp
//* @brief :Effekseerを使用したエフェクト再生クラス
//* @date  :2017/05/04
//* @author:S.Katou
//************************************************/
#include "Effect.h"
#include <xaudio2.h>

// デバイス
ID3D11Device* ShunLib::Effect::m_device;

//デバイスコンテキスト
ID3D11DeviceContext* ShunLib::Effect::m_context;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デバイスの設定
//｜引数  :デバイス
//｜引数  :デバイスコンテキスト
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void ShunLib::Effect::SetDevice(ID3D11Device* device,
							    ID3D11DeviceContext* context)
{
	m_device = device;
	m_context = context;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :ファイル指定コンストラクタ	
//｜引数  :cmoファイルの名前(wchar_t[])
//＋ーーーーーーーーーーーーーー＋
ShunLib::Effect::Effect(const wchar_t efk[])
{
	// 描画管理インスタンスの生成
	renderer = EffekseerRendererDX11::Renderer::Create(m_device, m_context, 32);
	
	// エフェクト管理用インスタンスの生成
	manager = Effekseer::Manager::Create(32);

	// 描画方法の指定、独自に拡張しない限り定形文です。
	manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
	manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
	manager->SetRingRenderer(renderer->CreateRingRenderer());
	
	// テクスチャ画像の読込方法の指定(パッケージ等から読み込む場合拡張する必要があります。)
	manager->SetTextureLoader(renderer->CreateTextureLoader());

	// 座標系の指定(RHで右手系、LHで左手系)
	manager->SetCoordinateSystem(Effekseer::CoordinateSystem::RH);

	// エフェクトの読込
	effect = Effekseer::Effect::Create(manager, (EFK_CHAR*)L"Effect\\Gravity.efk");

	// エフェクトの再生
	handle = manager->Play(effect, 0.0f, 0.0f, 0.0f);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
ShunLib::Effect::~Effect()
{
	// エフェクトを解放します。再生中の場合は、再生が終了した後、自動的に解放されます。
	ES_SAFE_RELEASE(effect);
	// エフェクト管理用インスタンスを破棄
	manager->Destroy();
	// 描画用インスタンスを破棄
	renderer->Destory();
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :モデルの描画
//｜引数  :位置ベクトル	(Vec3)
//｜引数  :ビュー行列	(Matrix)
//｜引数  :射影行列		(Matrix)
//｜引数  :拡大率		(Vec3)
//｜戻り値:なし(void)	
//＋ーーーーーーーーーーーーーー＋
void ShunLib::Effect::Draw(const ShunLib::Vec3 pos,
						   const ShunLib::Matrix& view,		
						   const ShunLib::Matrix & proj, 
						   const ShunLib::Vec3 scale)
{
	//位置ベクトルコピー
	Effekseer::Vector3D e_pos = { pos.m_x,pos.m_y,pos.m_z };

	//行列をコピー
	Effekseer::Matrix44 e_view;
	Effekseer::Matrix44 e_proj;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			e_view.Values[i][j] = view.m_value[i][j];
			e_proj.Values[i][j] = proj.m_value[i][j];
		}
	}

	
	// 再生中のエフェクトの移動
	manager->SetLocation(handle, e_pos);

	//拡大率
	manager->SetScale(handle, scale.m_x,scale.m_y,scale.m_z);

	// 投影行列の更新
	renderer->SetProjectionMatrix(e_proj);
	
	// カメラ行列の更新
	renderer->SetCameraMatrix(e_view);

	// 全てのエフェクトの更新
	manager->Update();

	//描画
	renderer->BeginRendering();
	manager->Draw();
	renderer->EndRendering();
}
