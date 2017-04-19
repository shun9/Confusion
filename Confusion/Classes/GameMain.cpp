//************************************************/
//* @file  :GameMain.cpp
//* @brief :�Q�[���̃��C���N���X�@���\�b�h�L���p
//* @date  :2017/04/18
//* @author:S.Katou
//************************************************/
#include "GameMain.h"
#include "Wrapper\Vec3\Vec3.h"

using namespace ShunLib;


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :����������
//�b����  :�X�N���[���̉���(int)
//�b����  :�X�N���[���̏c��(int)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void GameMain::Initialize(int screenW, int screenH)
{
	m_view = Matrix::CreateLookAt(Vec3(0.0f,0.0f,5.0f),Vec3::Zero,Vec3::UnitY);
	m_proj = Matrix::CreateProj(45.0f, static_cast<float>(screenW / screenH), 0.1f, 100.0f);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void GameMain::Update()
{
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void GameMain::Render()
{

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�I������
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void GameMain::Finalize()
{

}
