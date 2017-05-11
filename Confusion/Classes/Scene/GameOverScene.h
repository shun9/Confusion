//************************************************/
//* @file  :GameOverScene.h
//* @brief :�Q�[���I�[�o�[��ʂ̃N���X
//* @date  :2017/05/09
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"
class GamePadManager;

class GameOverScene:public Scene
{
private:
	GamePadManager* m_gamePad;

public:
	GameOverScene();
	~GameOverScene();
	void Update()override;
	void Render()override;
};