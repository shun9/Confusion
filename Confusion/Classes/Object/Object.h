//************************************************/
//* @file  :Object.h
//* @brief :�I�u�W�F�N�g�̊��N���X
//* @date  :2017/04/20
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Wrapper/Model/Model.h"
#include "../Wrapper/Vec3/Vec3.h"
#include "../Wrapper/Matrix/Matrix.h"


class Object
{
protected:
	//���f���f�[�^
	ShunLib::Model* m_model;

	//�ʒu
	ShunLib::Vec3* m_pos;
	
	//���x
	ShunLib::Vec3* m_spd;

	//�����̕���
	float m_angle;

public:
	//�R���X�g���N�^���f�X�g���N�^
	Object(const wchar_t* model,ShunLib::Vec3 pos = (0.0f,0.0f,0.0f));
	~Object();
	
	//�X�V����
	virtual void Update() = 0;
	
	//�`�揈��
	void Draw(const ShunLib::Matrix& view,
		      const ShunLib::Matrix& proj);
private:
	//�������v�Z����
	void CalculateDirection();
};
