//************************************************/
//* @file  :Scene.h
//* @brief :�V�[���̊��N���X
//* @date  :2017/05/02
//* @author:S.Katou
//************************************************/
#pragma once

class Scene
{
public:
	//�V�[���̎��
	enum
	{
		TITLE,
		PLAY,
	};

protected:
	//���̃V�[��
	static int m_nextScene;

public:
	//���̃V�[����Ԃ�
	static int NextScene() { return m_nextScene; }

public:
	~Scene() {}
	virtual void Update() = 0;
	virtual void Render() = 0;

};

