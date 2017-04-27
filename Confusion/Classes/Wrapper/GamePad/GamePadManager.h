//************************************************/
//* @file  :GamePadManeger.h
//* @brief :ゲームパッドの状態管理用ラップクラス
//* @date  :2017/04/22
//* @author:S.Katou
//************************************************/
#pragma once
#include <GamePad.h>
#include <vector>
#include "../../Player/Player.h"

class GamePadManager
{
public:
	static GamePadManager* GamePadManager::GetInstance();


private:
	//ゲームパッド
	std::unique_ptr<DirectX::GamePad>m_gamePad;

	//ゲームパッドの状態
	DirectX::GamePad::State m_state1;
	DirectX::GamePad::State m_state2;

public:
	//更新処理
	void Update();

	//状態を返す
	DirectX::GamePad::State Get(int gamePadNum);


	//設定関連
	void Suspend() { m_gamePad->Suspend(); }
	void Resume() { m_gamePad->Resume(); }

	/*--隠蔽--*/
private:
	//コンストラクタ＆デストラクタ
	GamePadManager();
	~GamePadManager();
};
