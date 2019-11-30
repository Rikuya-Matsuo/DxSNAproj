#include "DxLib.h"
#include "System.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (System::GetInstance().Init(true))
	{
		System::GetInstance().Run();
	}

	System::GetInstance().Finish();
}
