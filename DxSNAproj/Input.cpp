#include "Input.h"

Input::Input()
{
	for (int i = 0; i < mKeyMaxMass; ++i)
	{
		mKeyState[i] = 0x0F;
	}
}

Input::~Input()
{
}

void Input::Update()
{
	char tmp[mKeyMaxMass];
	memcpy(tmp, mKeyState, mKeyMaxMass);

	GetHitKeyStateAll(mKeyState);

	for (int i = 0; i < mKeyMaxMass; ++i)
	{
		mKeyState[i] |= tmp[i] << 1;
		// ���ʂQ�r�b�g�ȊO������
		mKeyState[i] &= 0x03;
	}
}
