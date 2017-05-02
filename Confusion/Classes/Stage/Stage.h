//************************************************/
//* @file  :Stage.h
//* @brief :�X�e�[�W�̃w�b�_�[
//* @date  :2017/05/01
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Wrapper/Model/Model.h"

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
	void Draw(const ShunLib::Matrix& view,
			  const ShunLib::Matrix& proj);
};