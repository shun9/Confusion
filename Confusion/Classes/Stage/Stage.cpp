//************************************************/
//* @file  :Stage.cpp
//* @brief :�X�e�[�W�`��p�̃N���X
//* @date  :2017/05/14
//* @author:S.Katou
//************************************************/
#include "Stage.h"

#include "../Scene/PlayScene.h"

Stage::Stage()
{
	using namespace ShunLib;
	//m_ground = new Texture(L"Images\\glass.jpg");
	m_ground = new Model(L"CModel\\Glass.cmo");
	m_tree = new Model(L"CModel\\tree.cmo");
}

Stage::~Stage()
{
	delete m_ground;
	delete m_tree;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`��
//�b����  :�r���[�s��		   (ShunLib::Matrix)
//�b����  :�v���W�F�N�V�����s��(ShunLib::Matrix)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Stage::Draw(const ShunLib::Matrix& world,
				 const ShunLib::Matrix& view,
				 const ShunLib::Matrix& proj)
{
	using namespace ShunLib;

	//�n�ʕ`��
	m_ground->Draw(world, view, proj);

	//�ؕ`��
	for (int i = 0; i < 20; i++)
	{
		Matrix worldLeft = Matrix::CreateTranslation(Vec3(PlayScene::STAGE_LEFT-3.0f, 0.0f, 25.0f - 4 * i));
		Matrix worldRight = Matrix::CreateTranslation(Vec3(PlayScene::STAGE_RIGHT+3.0f, 0.0f, 25.0f - 4 * i));
		m_tree->Draw(worldLeft, view, proj);
		m_tree->Draw(worldRight, view, proj);
	}
}
