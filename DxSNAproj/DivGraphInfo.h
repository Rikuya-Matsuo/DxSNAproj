#pragma once
#include "Vector.h"
#include <string>

struct DivGraphInfo
{
	// �t�@�C����
	std::string fileName;

	// �S�R�}��
	short frameMass;

	// ���ɕ���ł���R�}��
	short xNum;

	// �c�ɕ���ł���R�}��
	short yNum;

	// �R�}�ꖇ������̃T�C�Y
	Vector2D size;
};
