//************************************************/
//* @file  :Conversion.cpp
//* @brief :�ϊ��n�֐��u����
//* @date  :2017/02/21
//* @author:S.Katou
//************************************************/
#include"Conversion.h"

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�p�x���烉�W�A���ɕϊ�	
//�b����  :�p�x		(float)
//�b�߂�l:���W�A�� (float)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
float ShunLib::ToRadian(float angle)
{
	float radian = 0.0f;

	radian = angle * PI / 180.0f;

	return radian;
}



//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :���W�A������p�x�ɕϊ�	
//�b����  :���W�A��(float)
//�b�߂�l:�p�x�@�@(float)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
float ShunLib::ToAngle(float radian)
{
	float angle = 0.0f;
	
	angle = radian * 180.0f / PI;
	
	return angle;
}