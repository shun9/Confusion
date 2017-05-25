//************************************************/
//* @file  :Effect.cpp
//* @brief :Effekseerを使用したエフェクト再生クラス
//* @date  :2017/05/04
//* @author:S.Katou
//************************************************/
#include "Effect.h"
#include "../ConstantNumber/MacroConstants.h"

// デバイス
Microsoft::WRL::ComPtr<ID3D11Device>ShunLib::Effect::m_device;

//デバイスコンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext>ShunLib::Effect::m_context;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デバイスの設定
//｜引数  :デバイス
//｜引数  :デバイスコンテキスト
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void ShunLib::Effect::SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
								Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
{
	m_device = device;
	m_context = context;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :ファイル指定コンストラクタ
//｜引数  :cmoファイルの名前(wchar_t[])
//＋ーーーーーーーーーーーーーー＋
ShunLib::Effect::Effect(const wchar_t efk[], int flame, int spriteNum, bool isDrawFirst)
	: m_flame(flame)
	, m_flameCnt(0)
	, m_isEnded(false)
	, m_spd(1.0f)
{
	// 描画管理インスタンスの生成
	renderer = EffekseerRendererDX11::Renderer::Create(m_device.Get(), m_context.Get(), spriteNum);

	// エフェクト管理用インスタンスの生成
	manager = Effekseer::Manager::Create(spriteNum);

	// 描画方法の指定、独自に拡張しない限り定形文です。
	manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
	manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
	manager->SetRingRenderer(renderer->CreateRingRenderer());

	// テクスチャ画像の読込方法の指定(パッケージ等から読み込む場合拡張する必要があります。)
	manager->SetTextureLoader(renderer->CreateTextureLoader());

	// 座標系の指定(RHで右手系、LHで左手系)
	manager->SetCoordinateSystem(Effekseer::CoordinateSystem::RH);

	// エフェクトの読込
	effect = Effekseer::Effect::Create(manager, (EFK_CHAR*)efk);

	if (isDrawFirst) { handle = manager->Play(effect, 0.0f, 0.0f, 0.0f); }
	else { m_isEnded = true; }
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
ShunLib::Effect::~Effect()
{
	using namespace ShunLib;

	// エフェクトを解放します。再生中の場合は、再生が終了した後、自動的に解放されます。
	ES_SAFE_RELEASE(effect);
	// エフェクト管理用インスタンスを破棄
	manager->Destroy();
	// 描画用インスタンスを破棄
	renderer->Destory();
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :エフェクトの描画
//｜引数  :ビュー行列	(Matrix)
//｜引数  :射影行列		(Matrix)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void ShunLib::Effect::Draw(const ShunLib::Matrix& view,
						   const ShunLib::Matrix & proj)
{
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

	m_flameCnt++;

	if (m_flameCnt >= m_flame / m_spd)
	{
		m_isEnded = true;
	}
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :エフェクトの描画(ループ)
//｜引数  :ビュー行列	(Matrix)
//｜引数  :射影行列		(Matrix)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void ShunLib::Effect::DrawLoop(const ShunLib::Matrix& view, const ShunLib::Matrix & proj)
{

	this->Draw(view, proj);

	if (m_flameCnt >= m_flame)
	{
		m_flameCnt = 0;
		this->SetDraw();
	}
}
