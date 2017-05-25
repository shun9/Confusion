//************************************************/
//* @file  :Scene.h
//* @brief :シーンの基底クラス
//* @date  :2017/05/23
//* @author:S.Katou
//************************************************/
#pragma once

class Scene
{
public:
	//シーンの種類
	enum
	{
		TITLE,
		PLAY,
		CLEAR,
		OVER,
		EXIT,
	};

protected:
	//次のシーン
	static int m_nextScene;

public:
	//次のシーンを返す
	static int NextScene() { return m_nextScene; }

public:
	virtual ~Scene() {}
	virtual void Update() = 0;
	virtual void Render() = 0;

};

