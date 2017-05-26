//************************************************/
//* @file  :MacroConstants.h
//* @brief :自作マクロ定数まとめ
//* @date  :2017/05/10
//* @author:S.Katou
//************************************************/
#pragma once

namespace ShunLib
{
	//ポインター消去用
#define DELETE_POINTER(p) if (p!=nullptr){delete p; p = nullptr;}

}