//************************************************/
//* @file  :Stage.h
//* @brief :ステージのヘッダー
//* @date  :2017/05/01
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Wrapper/Model/Model.h"

class Stage
{
private:
	//地面と木のモデル
	ShunLib::Model* m_ground;
	ShunLib::Model* m_tree;

public:
	Stage();
	~Stage();

	//描画
	void Draw(const ShunLib::Matrix& view,
			  const ShunLib::Matrix& proj);
};