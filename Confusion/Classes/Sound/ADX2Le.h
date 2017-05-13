//--------------------------------------------------------------------------------------
// File: ADX2Le.cpp
//
// ADX2Leに関する関数群
//
// Date: 2015.10.1
// Author: Hideyasu Imase
//
// 簡単な使い方
//--------------------------------------------------------------------------------------
// ADX2Leの組み込み方
//
// １・cri_ware_pcx86_LE.dllをexeファイルのあるフォルダにコピーする
// ２・cri\pc\includeへパスを通す
// ３・cri\pc\libs\x86へパスを通す
// ４・cri_ware_pcx86_LE_import.libをリンクする
//     ※ #pragma comment(lib, "cri_ware_pcx86_LE_import.lib")で指定してもOK
//--------------------------------------------------------------------------------------
// 初期化：最初１回呼び出してください
//          ADX2Le::Initialize("ACFファイル名");
//
// 更新：毎フレーム呼び出してください
//          ADX2Le::Update();
//
// 終了処理：プログラム終了時に呼び出してください
//          ADX2Le::Finalize();
//--------------------------------------------------------------------------------------
// 音データのロード：AWBファイルは省略可
//          ADX2Le::LoadAcb("ACBファイル名", "AWBファイル名");
//
// 再生
//          ADX2Le::Play(キューインデックス);
//
// 停止
//          ADX2Le::Stop();
//
// ポーズ＆ポーズ解除
//          ADX2Le::Pause();
//
// 音量設定
//          ADX2Le::SetVolume(音量[1.0fが通常]);
//
// ※再生音ごとの音量変化やポーズなど指定できますがここでの説明は割愛します
//--------------------------------------------------------------------------------------
// 詳しいことを知りたい方はCRI ADX2のヘルプファイルを参照してください
// ヘルプファイル：cri\documentation\CRI_ADX2LE_PC_Manual_j.chm
//--------------------------------------------------------------------------------------
#pragma once

#include <cri_adx2le.h>

// ADX2Leの再生プレイヤークラス
class ADX2Le_Player
{
	// ACBハンドル
	CriAtomExAcbHn m_acb_hn;

	// プレイヤーハンドル
	CriAtomExPlayerHn m_player;

public:

	// コンストラクタ
	ADX2Le_Player();

	// プレイヤーの作成
	void Create();

	// Acbファイルのロード
	void LoadAcb(const char *acb, const char *awb = NULL);

	// プレイヤーの解放関数
	void Release();

	// プレイヤーハンドルの取得
	CriAtomExPlayerHn GetPlayerHandle();

	//----- 再生 -----//

	// 指定キューの再生 
	CriAtomExPlaybackId Play(CriAtomExCueId cue_id, float volume = 1.0f);

	//----- 音量 -----//

	// プレイヤーの音量の設定
	void SetVolume(float volume);

	// 再生ID指定の音量の設定
	void SetVolumeByID(CriAtomExPlaybackId playback_id, float volume);

	//----- ポーズ -----//

	// プレイヤーのポーズ
	void Pause();

	// 再生ID指定のポーズ
	void PauseByID(CriAtomExPlaybackId playback_id);

	// プレイヤーのポーズ状態の取得
	bool IsPause();

	// 再生ID指定のポーズ状態の取得
	bool IsPauseByID(CriAtomExPlaybackId playback_id);

	//----- 停止 -----//

	// プレイヤーの停止
	void Stop();

	// 特定の再生音の停止
	void StopByID(CriAtomExPlaybackId playback_id);

};

// ADX2Leクラス
class ADX2Le
{
	// 最大ボイス数を増やすための関連パラメータ
	static const int MAX_VOICE = 24;
	static const int MAX_VIRTUAL_VOICE = 64;	// ざっくり多め(通常ボイス＋HCA-MXボイス＋α)
	static const int MAX_CRIFS_LOADER = 64;		// ざっくり多め(通常ボイス＋HCA-MXボイス＋α)

	// 最大サンプリングレート（ピッチ変更含む）
	static const int MAX_SAMPLING_RATE = (48000 * 2);

	// HCA-MXコーデックのサンプリングレート
	static const int SAMPLINGRATE_HCAMX = 32000;

	static CriAtomExVoicePoolHn	m_standard_voice_pool;	// ボイスプール(ADX/HCAコーデック用)
	static CriAtomExVoicePoolHn	m_hcamx_voice_pool;		// ボイスプール(HCA-MX用)
	static CriAtomDbasId		m_dbas_id;				// D-BASハンドル

	static ADX2Le_Player m_player; // プレイヤー

private:
	static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
	static void *user_alloc_func(void *obj, CriUint32 size);
	static void user_free_func(void *obj, void *ptr);

public:

	// 初期化処理
	static void Initialize(const char *acf);

	// 更新処理
	static void Update();

	// 終了処理
	static void Finalize();

	// プレイヤーの取得関数
	static ADX2Le_Player* GetPlayer();

	// Acbファイルのロード
	static void LoadAcb(const char *acb, const char *awb = NULL);

	//----- 再生 -----//

	// 指定キューの再生 
	static CriAtomExPlaybackId Play(CriAtomExCueId cue_id, float volume = 1.0f);

	//----- 音量 -----//

	// プレイヤーの音量の設定
	static void SetVolume(float volume);

	//----- ポーズ -----//

	// プレイヤーのポーズ
	static void Pause();

	// プレイヤーのポーズ状態の取得
	static bool IsPause();

	//----- 停止 -----//

	// プレイヤーの停止
	static void Stop();

};
