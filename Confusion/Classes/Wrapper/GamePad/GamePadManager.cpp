//************************************************/
//* @file  :GamePadManeger.cpp
//* @brief :ゲームパッドの状態管理用ラップクラス
//* @date  :2017/04/22
//* @author:S.Katou
//************************************************/
#include "GamePadManager.h"

//＋ーーーーーーーーーーーーーー＋
//｜機能  :インスタンスの生成　取得
//｜引数  :なし(void)
//｜戻り値:インスタンス(Key*)	
//＋ーーーーーーーーーーーーーー＋
GamePadManager* GamePadManager::GetInstance()
{
	static GamePadManager gamePad;

	return &gamePad;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :ゲームパッドの状態を更新
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void GamePadManager::Update()
{
	m_state1 = m_gamePad->GetState(0);
	m_state2 = m_gamePad->GetState(1);
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :ゲームパッドの状態を返す
//｜引数  :なし(int)
//｜戻り値:ゲームパッドの状態を返す(DirectX::GamePad::State)
//＋ーーーーーーーーーーーーーー＋
DirectX::GamePad::State GamePadManager::Get(int gamePadNum)
{ 
	switch (gamePadNum)
	{
	case 0:
		return m_state1;
	case 1:
		return m_state2;

	default:
		break;
	}
	return m_state1; 
}


/*--以下隠蔽--*/
//コンストラクタ＆デストラクタ
GamePadManager::GamePadManager()
{
	m_gamePad = std::make_unique<DirectX::GamePad>();
	m_state1 = m_gamePad->GetState(0);
	m_state2 = m_gamePad->GetState(1);
}


GamePadManager::~GamePadManager() 
{
}
