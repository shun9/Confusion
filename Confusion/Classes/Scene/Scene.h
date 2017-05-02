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
		TITLE,
		PLAY,
	};

private:
	static int m_nextScene;

public:
	~Scene() {}
	virtual void Update() = 0;
	virtual void Render() = 0;

	//次のシーンを返す
	int NextScene() { return m_nextScene; }
};
