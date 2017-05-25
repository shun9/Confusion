//************************************************/
//* @file  :Stage.h
//* @brief :�X�e�[�W�`��p�̃N���X
//* @date  :2017/05/24
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Wrapper/Model/Model.h"
#include "../Wrapper/Texture/Texture.h"

class Stage
{
private:
	//�n�ʂƖ؂̃��f��
	ShunLib::Model* m_ground;
	ShunLib::Model* m_tree;

public:
	Stage();
	~Stage();

	//�`��
	void Draw(const ShunLib::Matrix& world,
			  const ShunLib::Matrix& view,
			  const ShunLib::Matrix& proj,
			  bool  isDrawTree = true);
};