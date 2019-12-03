#include "DxLib.h"
#include "System.h"
#include "TestScene00.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (System::GetInstance().Init(true))
	{
		System::GetInstance().SetScene(new TestScene00);

		System::GetInstance().Run();
	}

	System::GetInstance().Finish();
}
