//************************************************/
//* @file  :Matrix.cpp
//* @brief :�s��p�̃��b�v�N���X
//* @date  :2017/02/22
//* @author:S.Katou & K.Yamamoto
//************************************************/
#include "Matrix.h"

using namespace ShunLib;

Matrix Matrix::Identity;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :���s�ړ��s��̍쐬
//�b����  :�ړ���̈ʒu(Vec3)
//�b�߂�l:�s��(Matrix)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix Matrix::CreateTranslation(const Vec3& pos)
{
	Matrix matrix;
	matrix.m_value[3][0] += pos.m_x;
	matrix.m_value[3][1] += pos.m_y;
	matrix.m_value[3][2] += pos.m_z;

	return matrix;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�w����]�s��̍쐬
//�b����  :�p�x(float)
//�b�߂�l:�s��(Matrix)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix Matrix::CreateRotationX(float angle)
{
	Matrix matrix;
	matrix.m_value[1][1] =  cos(DirectX::XMConvertToRadians(angle));
	matrix.m_value[1][2] = -sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[2][1] =  sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[2][2] =  cos(DirectX::XMConvertToRadians(angle));

	return matrix;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�x����]�s��̍쐬
//�b����  :�p�x(float)
//�b�߂�l:�s��(Matrix)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix Matrix::CreateRotationY(float angle)
{
	Matrix matrix;
	matrix.m_value[0][0] =  cos(DirectX::XMConvertToRadians(angle));
	matrix.m_value[0][2] =  sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[2][0] = -sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[2][2] =  cos(DirectX::XMConvertToRadians(angle));

	return matrix;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�y����]�s��̍쐬
//�b����  :�p�x(float)
//�b�߂�l:�s��(Matrix)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix Matrix::CreateRotationZ(float angle)
{
	Matrix matrix;
	matrix.m_value[0][0] =  cos(DirectX::XMConvertToRadians(angle));
	matrix.m_value[0][1] = -sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[1][0] =  sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[1][1] =  cos(DirectX::XMConvertToRadians(angle));

	return matrix;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�g��k���s��̍쐬
//�b����  :�g�嗦(Vec3)
//�b�߂�l:�s��(Matrix)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix Matrix::CreateScale(const Vec3& scale)
{

	Matrix matrix;
	matrix.m_value[0][0] *= scale.m_x;
	matrix.m_value[1][1] *= scale.m_y;
	matrix.m_value[2][2] *= scale.m_z;

	return matrix;
}



//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�g��k���s��̍쐬
//�b����  :�g�嗦(float)
//�b�߂�l:�s��(Matrix)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix Matrix::CreateScale(float scale)
{
	Matrix matrix;
	matrix.m_value[0][0] *= scale;
	matrix.m_value[1][1] *= scale;
	matrix.m_value[2][2] *= scale;

	return matrix;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�ˉe�s��̍쐬
//�b����  :����p�@�@�@�@�@�@(float)
//�b����  :�A�X�y�N�g��@�@�@(float)
//�b����  :�߃N���b�v�ʂ̋���(float)
//�b����  :���N���b�v�ʂ̋���(float)
//�b�߂�l:�ˉe�s��(Matrix)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix Matrix::CreateProj(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	Matrix proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(DirectX::XMConvertToRadians(fov),aspectRatio,nearPlane, farPlane);
	return proj;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�r���[�s��̍쐬
//�b����  :�J�����̈ʒu�@�@�@(Vec3)
//�b����  :�J�����̒����_�@�@(Vec3)
//�b����  :�J�����̏������  (Vec3)
//�b�߂�l:�r���[�s��		 (Matrix)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix ShunLib::Matrix::CreateLookAt(ShunLib::Vec3 eye, ShunLib::Vec3 target, ShunLib::Vec3 up)
{
	DirectX::SimpleMath::Matrix view;
	DirectX::SimpleMath::Vector3 eyev = eye.GetDirectVec3();
	DirectX::SimpleMath::Vector3 targetv = target.GetDirectVec3();
	DirectX::SimpleMath::Vector3 upv = up.GetDirectVec3();
	view = DirectX::SimpleMath::Matrix::CreateLookAt(eyev,targetv ,upv);

	return view;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�t�H���g�R���X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix::Matrix()
{
	
	float matrix[4][4] =
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_value[i][j] = matrix[i][j];
		}
	}

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R�s�[�R���X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix::Matrix(const Matrix& M)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m_value[i][j] = M.m_value[i][j];
		}
	}
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :DirectX�s��ϊ��R���X�g���N�^
//�b����  :DirectX�̍s��(DirectX::SimpleMath::Matrix)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix::Matrix(const DirectX::SimpleMath::Matrix& M)
{
	float m[4][4] =
	{
		{ M._11,M._12,M._13,M._14 },
		{ M._21,M._22,M._23,M._24 },
		{ M._31,M._32,M._33,M._34 },
		{ M._41,M._42,M._43,M._44 },
	};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m_value[i][j] = m[i][j];
		}
	}

}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Matrix::~Matrix()
{
	
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�s���DirectX�̌`���ŕԂ�
//�b����  :�Ȃ�(void)
//�b�߂�l:�s��(Matrix)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
DirectX::SimpleMath::Matrix Matrix::GetDirectMatrix()const
{
	DirectX::SimpleMath::Matrix matrix =
		DirectX::SimpleMath::Matrix(m_value[0][0], m_value[0][1], m_value[0][2], m_value[0][3],
									m_value[1][0], m_value[1][1], m_value[1][2], m_value[1][3],
									m_value[2][0], m_value[2][1], m_value[2][2], m_value[2][3],
									m_value[3][0], m_value[3][1], m_value[3][2], m_value[3][3]);
	return matrix;
}



/*--[�ȉ����Z�q�̃I�[�o�[���[�h]--*/

Matrix& Matrix::operator=(const Matrix& M)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m_value[i][j] = M.m_value[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator=(const DirectX::SimpleMath::Matrix& M)
{
	float m[4][4]=
	{
		{ M._11,M._12,M._13,M._14 },
		{ M._21,M._22,M._23,M._24 },
		{ M._31,M._32,M._33,M._34 },
		{ M._41,M._42,M._43,M._44 },
	};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m_value[i][j] = m[i][j];
		}
	}

	return *this;
}

Matrix Matrix::operator+(const Matrix& M)
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.m_value[i][j] = this->m_value[i][j] + M.m_value[i][j];
		}
	}

	return m;

	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

Matrix Matrix::operator-(const Matrix& M)
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.m_value[i][j]=this->m_value[i][j] - M.m_value[i][j];
		}
	}
	return m;
}

Matrix Matrix::operator*(const Matrix& M)
{
	Matrix m;

	// �P�s�ڂ̌v�Z
	float x = this->m_value[0][0];
	float y = this->m_value[0][1];
	float z = this->m_value[0][2];
	float w = this->m_value[0][3];
	m.m_value[0][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[0][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[0][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[0][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);
	
	// �Q�s�ڂ̌v�Z
	x = this->m_value[1][0];
	y = this->m_value[1][1];
	z = this->m_value[1][2];
	w = this->m_value[1][3];
	m.m_value[1][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[1][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[1][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[1][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	// �R�s�ڂ̌v�Z
	x = this->m_value[2][0];
	y = this->m_value[2][1];
	z = this->m_value[2][2];
	w = this->m_value[2][3];
	m.m_value[2][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[2][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[2][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[2][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	// �S�s�ڂ̌v�Z
	x = this->m_value[3][0];
	y = this->m_value[3][1];
	z = this->m_value[3][2];
	w = this->m_value[3][3];
	m.m_value[3][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[3][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[3][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[3][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);
	
	return m;
}

Matrix Matrix::operator*(int num)
{
	Matrix m;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j  < 4; j ++)
		{
			m.m_value[i][j]=this->m_value[i][j] * num;
		}
	}
	
	return m;
}
