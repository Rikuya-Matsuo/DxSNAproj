#include "System.h"
#include "Input.h"

System::System()
{

}

System::~System()
{
}

bool System::Init(bool windowModeFlag, float width, float height)
{
	mWindowSize.x = width;
	mWindowSize.y = height;

	SetGraphMode((int)mWindowSize.x, (int)mWindowSize.y, 16);

	ChangeWindowMode((windowModeFlag) ? TRUE : FALSE);

	if (DxLib_Init())
	{
		//ñ‚ëËî≠ê∂éûÇ…Ç±ÇÃÇ©Ç¡Ç±ÇÃíÜÇ…ì¸Ç¡ÇƒÇ¢ÇÈ
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
		Input::GetInstance().Update();

		if (ProcessMessage() || Input::GetInstance().GetKeyPressDown(KEY_INPUT_ESCAPE))
		{
			quitLoop = true;
		}
	}
}

void System::Finish()
{
	DxLib_End();
}
