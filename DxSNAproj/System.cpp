#include "System.h"

System::~System()
{
	DxLib_End();
}

bool System::Init(bool windowModeFlag, float width, float height)
{
	mWindowSize.x = width;
	mWindowSize.y = height;

	SetGraphMode((int)mWindowSize.x, (int)mWindowSize.y, 16);

	ChangeWindowMode((windowModeFlag) ? TRUE : FALSE);

	if (DxLib_Init())
	{
		//��蔭�����ɂ��̂������̒��ɓ����Ă���
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

void System::Run()
{
	bool quitLoop = false;
	while (!quitLoop)
	{

	}
}
