#include "System.h"
#include "Input.h"
#include "SpriteComponent.h"
#include <algorithm>

System::System():
	mPrevCount(GetNowCount()),
	mDeltaTime(0.0f),
	mSpriteSortFlag(false)
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
		//–â‘è”­¶Žž‚É‚±‚Ì‚©‚Á‚±‚Ì’†‚É“ü‚Á‚Ä‚¢‚é
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

		Draw();
	}
}

void System::Finish()
{
	SpriteComponent::Finish();

	DxLib_End();
}

void System::CalculateDeltaTime()
{
	int nowCount = GetNowCount();
	mDeltaTime = (nowCount - mPrevCount) / 1000.0f;
	
	// ’²®
	const float deltaTimeMax = 1.0f / 60;
	if (mDeltaTime > deltaTimeMax)
	{
		mDeltaTime = deltaTimeMax;
	}

	mPrevCount = nowCount;
}

void System::Draw()
{
	ClearDrawScreen();

	if (mSpriteSortFlag)
	{
		// ƒ‰ƒ€ƒ_Ž®
		bool(*drawOrderSort)(const SpriteComponent *, const SpriteComponent *)
			= [](const SpriteComponent * lhs, const SpriteComponent * rhs)
		{
			return lhs->GetDrawOrder() <= rhs->GetDrawOrder();
		};

		mSprites.sort(drawOrderSort);

		mSpriteSortFlag = false;
	}

	ScreenFlip();
}

void System::ResisterActor(const ActorBase * actor)
{
	mActors.emplace_back(const_cast<ActorBase*>(actor));
}

void System::DeresisterActor(const ActorBase * actor)
{
	auto itr = std::find(mActors.begin(), mActors.end(), const_cast<ActorBase*>(actor));
	
	if (itr != mActors.end())
	{
		mActors.erase(itr);
	}
}
