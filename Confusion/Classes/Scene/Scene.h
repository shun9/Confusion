//************************************************/
//* @file  :Scene.h
//* @brief :シーンの基底クラス
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#pragma once

class Scene
{
public:
	enum
	{
		PLAY,
	};

	static int nextScene;

public:
	~Scene() {}
	virtual void Update() = 0;
	virtual void Render() = 0;

};
