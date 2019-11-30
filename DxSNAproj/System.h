#pragma once
#include "DxLib.h"
#include "Vector.h"

class System final
{
public:
	~System();

	static System & GetInstance()
	{
		static System instance;
		return instance;
	}

	bool Init(bool windowModeFlag, float width = 1920.0f, float height = 1080.0f);

	void Run();

private:
	System();

	Vector2D mWindowSize;
};
