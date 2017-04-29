//************************************************/
//* @file  :Gravity.h
//* @brief :プレイヤーが発する重力のクラス
//* @date  :2017/04/23
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Wrapper/Texture/Texture.h"
#include "../Wrapper/Matrix/Matrix.h"

class Gravity
{
private:
	static const float POWER;

private:
	ShunLib::Texture* m_texture;

	//半径
	float m_radius;

	//位置
	ShunLib::Vec3 m_pos;

	//回転用
	float m_angle;

public:
	//コンストラクタ＆デストラクタ
	Gravity(const wchar_t* texture,
			const ShunLib::Vec3& pos = (0.0f, 0.0f, 0.0f));
	~Gravity();

	//更新
	void Update();

	//描画
	void Draw(ShunLib::Matrix view, ShunLib::Matrix proj);

	//半径
	void Radius(float radius) { m_radius = radius; }
	float Radius() { return m_radius; }

	//位置
	void Pos(ShunLib::Vec3 pos) { m_pos = pos; }
	void Pos(float x,float y,float z) 
	{
		m_pos.m_x = x; 
		m_pos.m_y = y;
		m_pos.m_z = z;
	}
	ShunLib::Vec3 Pos() { return m_pos; }

	//対象を引き寄せる
	void Attract(ShunLib::Vec3* objPos);
};
