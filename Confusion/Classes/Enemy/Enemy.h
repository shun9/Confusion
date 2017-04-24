//************************************************/
//* @file  :Enemy.h
//* @brief :敵のヘッダーファイル
//* @date  :2017/04/24
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Object/Object.h"
#include "../Wrapper/Vec3/Vec3.h"

class Enemy : public Object
{
private:

public:
	Enemy(const wchar_t* model, ShunLib::Vec3 pos = (0.0f, 0.0f, 0.0f));
	~Enemy();

	//更新
	void Update()override;
};
