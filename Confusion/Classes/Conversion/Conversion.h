//************************************************/
//* @file  :Conversion.h
//* @brief :変換系関数置き場
//* @date  :2017/02/20
//* @author:S.Katou
//************************************************/
#pragma once

namespace ShunLib
{
	//円周率
	const float PI = 3.14159265359f;

	//角度からラジアンに変換
	float ToRadian(float angle);

	//ラジアンから角度に変換
	float ToAngle(float radian);
}
