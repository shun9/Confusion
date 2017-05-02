//************************************************/
//* @file  :Scene.h
//* @brief :�V�[���̊��N���X
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

	//���̃V�[����Ԃ�
	int NextScene() { return m_nextScene; }
};
