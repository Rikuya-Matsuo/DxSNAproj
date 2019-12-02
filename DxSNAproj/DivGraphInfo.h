#pragma once
#include "Vector.h"
#include <string>

struct DivGraphInfo
{
	// ファイル名
	std::string fileName;

	// 全コマ数
	short frameMass;

	// 横に並んでいるコマ数
	short xNum;

	// 縦に並んでいるコマ数
	short yNum;

	// コマ一枚当たりのサイズ
	Vector2D size;
};
