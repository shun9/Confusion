#include "Model.h"
#include <SimpleMath.h>
#include "../Matrix/Matrix.h"

using namespace ShunLib;

//デバイス関連
ID3D11Device* Model::m_device;
ID3D11DeviceContext* Model::m_context;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デバイスの設定
//｜引数  :デバイス
//｜引数  :デバイスコンテキスト
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void ShunLib::Model::SetDevice(ID3D11Device* device, 
							   ID3D11DeviceContext* context)
{
	m_device  = device;
	m_context = context;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :ファイル指定コンストラクタ	
//｜引数  :cmoファイルの名前(wchar_t[])
//＋ーーーーーーーーーーーーーー＋
Model::Model(const wchar_t cmo[])
{
	//ステート作成
	m_state = std::make_unique<DirectX::CommonStates>(m_device);
	
	//エフェクト作成
	m_effect = std::make_unique<DirectX::EffectFactory>(m_device);

	//テクスチャの場所を指定
	m_effect->SetDirectory(L"CModel");

	//モデルの作成
	m_model = DirectX::Model::CreateFromCMO(m_device,cmo, *m_effect);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Model::~Model()
{
	m_state.reset();
	m_effect.reset();
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
	m_model->Draw(m_context, *m_state, w, v, p);
}
