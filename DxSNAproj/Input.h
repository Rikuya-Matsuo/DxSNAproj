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

	// �ŉ��ʃr�b�g�����݂̏�ԁA������2�Ԗڂ��O�t���[���̏��
	char mKeyState[mKeyMaxMass];
};
