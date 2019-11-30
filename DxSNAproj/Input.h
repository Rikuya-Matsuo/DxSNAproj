#pragma once
#include "DxLib.h"

class Input final
{
public:
	~Input();

	static Input & GetInstance()
	{
		static Input instance;
		return instance;
	}

	void Update();

	bool GetKeyPressDown(int keyCode) const { return mKeyState[keyCode] == 1; }
	bool GetKeyPressed(int keyCode) const { return mKeyState[keyCode] == 3; }
	bool GetKeyRelease(int keyCode) const { return mKeyState[keyCode] == 2; }

private:
	Input();

	static const short mKeyMaxMass = 256;

	// 最下位ビットが現在の状態、下から2番目が前フレームの状態
	char mKeyState[mKeyMaxMass];
};
