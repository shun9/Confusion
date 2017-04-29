//************************************************/
//* @file  :TitleScene.h
//* @brief :タイトル画面のヘッダー
//* @date  :2017/04/29
//* @author:S.Katou
//************************************************/
#pragma once
#include "Scene.h"

class TitleScene : public Scene
{

public:
	TitleScene();
	~TitleScene();

	void Update()override;
	void Render()override;

};