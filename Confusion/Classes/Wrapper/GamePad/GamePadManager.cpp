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
	for (int i = 0; i < Player::MAX_PLAYER; i++)
	{
		m_state[i] = m_gamePad->GetState(i);
	}
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :ゲームパッドの状態を返す
//｜引数  :なし(void)
//｜戻り値:ゲームパッドの状態を返す(DirectX::GamePad::State)
//＋ーーーーーーーーーーーーーー＋
DirectX::GamePad::State GamePadManager::Get(int gamePadNum)
{ 
	return m_state[gamePadNum]; 
}


/*--以下隠蔽--*/
//コンストラクタ＆デストラクタ
GamePadManager::GamePadManager()
{

	m_gamePad = std::make_unique<DirectX::GamePad>();
	m_state = new DirectX::GamePad::State[Player::MAX_PLAYER];
}


GamePadManager::~GamePadManager() 
{
	delete[] m_state;
}
