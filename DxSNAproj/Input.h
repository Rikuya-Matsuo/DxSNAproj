#pragma once
#include "DxLib.h"

class Input final
{
public:
	Input();
	~Input();

	void Update();

private:
	static const short mKeyMaxMass = 256;
	char mKeyState[mKeyMaxMass];
};
