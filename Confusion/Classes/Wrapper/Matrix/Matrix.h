//************************************************/
//* @file  :Matrix.h
//* @brief :行列用のラップクラス
//* @date  :2017/02/21
//* @author:S.Katou & K.Yamamoto
//************************************************/
#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../Vec3/Vec3.h"

namespace ShunLib
{
	class Matrix
	{
		/*--[静的なやつら]--*/
	public:
		//単位行列
		static Matrix Identity;

	public:
		//平行移動行列
		static Matrix CreateTranslation(const Vec3& pos);

		//回転行列
		static Matrix CreateRotationX(float angle);
		static Matrix CreateRotationY(float angle);
		static Matrix CreateRotationZ(float angle);

		//拡大縮小行列
		static Matrix CreateScale(const Vec3& scale);
		static Matrix CreateScale(float scale);

		static Matrix CreateProj(float fov,
								 float aspectRatio,
							     float nearPlane,
							     float farPlane);

		// ビュー行列の作成
		static Matrix CreateLookAt(
			ShunLib::Vec3 eye, 
			ShunLib::Vec3 target, 
			ShunLib::Vec3 up);


		/*--[静的ではないやつら]--*/
	private:
		float m_matrix[4][4];

	public:
		Matrix();
		Matrix(const Matrix& M);
		Matrix(const DirectX::SimpleMath::Matrix& M);
		~Matrix();

		//行列をDirectXの形式で返す
		DirectX::SimpleMath::Matrix GetDirectMatrix()const;


		/*--[演算子のオーバーロード]--*/
		Matrix& operator=(const Matrix& M);
		Matrix& operator=(const DirectX::SimpleMath::Matrix& M);
		Matrix& operator+(const Matrix& M);
		Matrix& operator-(const Matrix& M);
		Matrix& operator*(const Matrix& M);
		Matrix& operator*(int num);
	};
}