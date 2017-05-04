//************************************************/
//* @file  :Matrix.cpp
//* @brief :行列用のラップクラス
//* @date  :2017/02/22
//* @author:S.Katou & K.Yamamoto
//************************************************/
#include "Matrix.h"

using namespace ShunLib;

Matrix Matrix::Identity;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :平行移動行列の作成
//｜引数  :移動後の位置(Vec3)
//｜戻り値:行列(Matrix)	
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateTranslation(const Vec3& pos)
{
	Matrix matrix;
	matrix.m_value[3][0] += pos.m_x;
	matrix.m_value[3][1] += pos.m_y;
	matrix.m_value[3][2] += pos.m_z;

	return matrix;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :Ｘ軸回転行列の作成
//｜引数  :角度(float)
//｜戻り値:行列(Matrix)	
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateRotationX(float angle)
{
	Matrix matrix;
	matrix.m_value[1][1] =  cos(DirectX::XMConvertToRadians(angle));
	matrix.m_value[1][2] = -sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[2][1] =  sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[2][2] =  cos(DirectX::XMConvertToRadians(angle));

	return matrix;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :Ｙ軸回転行列の作成
//｜引数  :角度(float)
//｜戻り値:行列(Matrix)	
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateRotationY(float angle)
{
	Matrix matrix;
	matrix.m_value[0][0] =  cos(DirectX::XMConvertToRadians(angle));
	matrix.m_value[0][2] =  sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[2][0] = -sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[2][2] =  cos(DirectX::XMConvertToRadians(angle));

	return matrix;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :Ｚ軸回転行列の作成
//｜引数  :角度(float)
//｜戻り値:行列(Matrix)	
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateRotationZ(float angle)
{
	Matrix matrix;
	matrix.m_value[0][0] =  cos(DirectX::XMConvertToRadians(angle));
	matrix.m_value[0][1] = -sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[1][0] =  sin(DirectX::XMConvertToRadians(angle));
	matrix.m_value[1][1] =  cos(DirectX::XMConvertToRadians(angle));

	return matrix;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :拡大縮小行列の作成
//｜引数  :拡大率(Vec3)
//｜戻り値:行列(Matrix)	
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateScale(const Vec3& scale)
{

	Matrix matrix;
	matrix.m_value[0][0] *= scale.m_x;
	matrix.m_value[1][1] *= scale.m_y;
	matrix.m_value[2][2] *= scale.m_z;

	return matrix;
}



//＋ーーーーーーーーーーーーーー＋
//｜機能  :拡大縮小行列の作成
//｜引数  :拡大率(float)
//｜戻り値:行列(Matrix)	
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateScale(float scale)
{
	Matrix matrix;
	matrix.m_value[0][0] *= scale;
	matrix.m_value[1][1] *= scale;
	matrix.m_value[2][2] *= scale;

	return matrix;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :射影行列の作成
//｜引数  :視野角　　　　　　(float)
//｜引数  :アスペクト比　　　(float)
//｜引数  :近クリップ面の距離(float)
//｜引数  :遠クリップ面の距離(float)
//｜戻り値:射影行列(Matrix)	
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateProj(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	Matrix proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(DirectX::XMConvertToRadians(fov),aspectRatio,nearPlane, farPlane);
	return proj;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :ビュー行列の作成
//｜引数  :カメラの位置　　　(Vec3)
//｜引数  :カメラの注視点　　(Vec3)
//｜引数  :カメラの上方方向  (Vec3)
//｜戻り値:ビュー行列		 (Matrix)	
//＋ーーーーーーーーーーーーーー＋
Matrix ShunLib::Matrix::CreateLookAt(ShunLib::Vec3 eye, ShunLib::Vec3 target, ShunLib::Vec3 up)
{
	DirectX::SimpleMath::Matrix view;
	DirectX::SimpleMath::Vector3 eyev = eye.GetDirectVec3();
	DirectX::SimpleMath::Vector3 targetv = target.GetDirectVec3();
	DirectX::SimpleMath::Vector3 upv = up.GetDirectVec3();
	view = DirectX::SimpleMath::Matrix::CreateLookAt(eyev,targetv ,upv);

	return view;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デフォルトコンストラクタ
//＋ーーーーーーーーーーーーーー＋
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


//＋ーーーーーーーーーーーーーー＋
//｜機能  :コピーコンストラクタ
//＋ーーーーーーーーーーーーーー＋
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


//＋ーーーーーーーーーーーーーー＋
//｜機能  :DirectX行列変換コンストラクタ
//｜引数  :DirectXの行列(DirectX::SimpleMath::Matrix)
//＋ーーーーーーーーーーーーーー＋
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

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ	
//＋ーーーーーーーーーーーーーー＋
Matrix::~Matrix()
{
	
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :行列をDirectXの形式で返す
//｜引数  :なし(void)
//｜戻り値:行列(Matrix)	
//＋ーーーーーーーーーーーーーー＋
DirectX::SimpleMath::Matrix Matrix::GetDirectMatrix()const
{
	DirectX::SimpleMath::Matrix matrix =
		DirectX::SimpleMath::Matrix(m_value[0][0], m_value[0][1], m_value[0][2], m_value[0][3],
									m_value[1][0], m_value[1][1], m_value[1][2], m_value[1][3],
									m_value[2][0], m_value[2][1], m_value[2][2], m_value[2][3],
									m_value[3][0], m_value[3][1], m_value[3][2], m_value[3][3]);
	return matrix;
}



/*--[以下演算子のオーバーロード]--*/

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

Matrix& Matrix::operator+(const Matrix& M)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m_value[i][j] += M.m_value[i][j];
		}
	}

	return *this;

	// TODO: return ステートメントをここに挿入します
}

Matrix& Matrix::operator-(const Matrix& M)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m_value[i][j] -= M.m_value[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*(const Matrix& M)
{
	// １行目の計算
	float x = this->m_value[0][0];
	float y = this->m_value[0][1];
	float z = this->m_value[0][2];
	float w = this->m_value[0][3];
	this->m_value[0][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	this->m_value[0][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	this->m_value[0][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	this->m_value[0][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);
	
	// ２行目の計算
	x = this->m_value[1][0];
	y = this->m_value[1][1];
	z = this->m_value[1][2];
	w = this->m_value[1][3];
	this->m_value[1][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	this->m_value[1][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	this->m_value[1][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	this->m_value[1][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	// ３行目の計算
	x = this->m_value[2][0];
	y = this->m_value[2][1];
	z = this->m_value[2][2];
	w = this->m_value[2][3];
	this->m_value[2][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	this->m_value[2][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	this->m_value[2][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	this->m_value[2][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	// ４行目の計算
	x = this->m_value[3][0];
	y = this->m_value[3][1];
	z = this->m_value[3][2];
	w = this->m_value[3][3];
	this->m_value[3][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	this->m_value[3][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	this->m_value[3][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	this->m_value[3][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);
	
	return *this;
}

Matrix& Matrix::operator*(int num)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j  < 4; j ++)
		{
			this->m_value[i][j] *= num;
		}
	}
	
	return *this;
}
