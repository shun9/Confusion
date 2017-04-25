//************************************************/
//* @file  :Object.h
//* @brief :オブジェクトの基底クラス
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
	//モデルデータ
	ShunLib::Model* m_model;

	//位置
	ShunLib::Vec3* m_pos;
	
	//速度
	ShunLib::Vec3* m_spd;

	//向きの方向
	float m_angle;

public:
	//コンストラクタ＆デストラクタ
	Object(const wchar_t* model,ShunLib::Vec3 pos = (0.0f,0.0f,0.0f));
	~Object();
	
	//更新処理
	virtual void Update() = 0;
	
	//描画処理
	void Draw(const ShunLib::Matrix& view,
		      const ShunLib::Matrix& proj);
private:
	//向きを計算する
	void CalculateDirection();
};
