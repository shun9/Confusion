//************************************************/
//* @file  :Conversion.cpp
//* @brief :変換系関数置き場
//* @date  :2017/02/21
//* @author:S.Katou
//************************************************/
#include"Conversion.h"

//＋ーーーーーーーーーーーーーー＋
//｜機能  :角度からラジアンに変換	
//｜引数  :角度		(float)
//｜戻り値:ラジアン (float)	
//＋ーーーーーーーーーーーーーー＋
float ShunLib::ToRadian(float angle)
{
	float radian = 0.0f;

	radian = angle * PI / 180.0f;

	return radian;
}



//＋ーーーーーーーーーーーーーー＋
//｜機能  :ラジアンから角度に変換	
//｜引数  :ラジアン(float)
//｜戻り値:角度　　(float)	
//＋ーーーーーーーーーーーーーー＋
float ShunLib::ToAngle(float radian)
{
	float angle = 0.0f;
	
	angle = radian * 180.0f / PI;
	
	return angle;
}