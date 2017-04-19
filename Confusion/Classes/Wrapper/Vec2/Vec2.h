//************************************************/
//* @file  :Vec2.h
//* @brief :2次元ベクトル用のラップクラス
//* @date  :2017/03/29
//* @author:K.Yamamoto
//************************************************/

// 多重インクルード防止
#pragma once

// ヘッダファイルのインクルード
#include <d3d11.h>
#include <SimpleMath.h>

// 名前空間使用
namespace YamagenLib
{
	// Vec2クラス
	class Vec2
	{
	public:
		float m_x;
		float m_y;

	public:
		Vec2();
		Vec2(float x, float y);
		~Vec2();

		// ベクトルをDirectXの形式で返す
		DirectX::SimpleMath::Vector2 GetDirectVec2();
	
		/*--[演算子のオーバーロード]--*/
		Vec2& operator=(const Vec2& V);
		Vec2& operator=(const DirectX::SimpleMath::Vector2& V);
		Vec2& operator+(const Vec2& V);
		Vec2& operator-(const Vec2& V);
		Vec2& operator*(int num);

	};
}