#include "Model.h"
#include <SimpleMath.h>
#include "../Matrix/Matrix.h"

using namespace ShunLib;

//デバイス関連
Microsoft::WRL::ComPtr<ID3D11Device> Model::m_device;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Model::m_context;

//エフェクトデータ
std::unique_ptr<DirectX::EffectFactory> Model::m_effect;
std::shared_ptr<DirectX::CommonStates> Model::m_state;


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デバイスの設定
//｜引数  :デバイス
//｜引数  :デバイスコンテキスト
//｜引数  :ステート
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void ShunLib::Model::SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device, 
							   Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
							   std::shared_ptr<DirectX::CommonStates> state)
{
	m_device  = device;
	m_context = context;
	m_state   = state;
	m_effect  = std::make_unique<DirectX::EffectFactory>(m_device.Get());
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :終了処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void ShunLib::Model::Release()
{
	m_effect->ReleaseCache();
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :ファイル指定コンストラクタ	
//｜引数  :cmoファイルの名前(wchar_t[])
//＋ーーーーーーーーーーーーーー＋
Model::Model(const wchar_t cmo[])
{
	m_model = DirectX::Model::CreateFromCMO(m_device.Get(),cmo, *m_effect);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Model::~Model()
{
	m_model.reset();
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :モデルの描画
//｜引数  :ワールド行列	(Matrix)
//｜引数  :ビュー行列	(Matrix)
//｜引数  :射影行列		(Matrix)
//｜戻り値:なし(void)	
//＋ーーーーーーーーーーーーーー＋
void Model::Draw(const Matrix& world,
				 const Matrix& view,
				 const Matrix& proj)
{
	DirectX::SimpleMath::Matrix w = world.GetDirectMatrix();	// ワールド
	DirectX::SimpleMath::Matrix v = view.GetDirectMatrix();		// ビュー
	DirectX::SimpleMath::Matrix p = proj.GetDirectMatrix();		// プロジェクション

	// 描画		 コンテキスト,ステート,ワールド,ビュー,プロジェクション
	m_model->Draw(m_context.Get() , *m_state, w, v, p);
}
