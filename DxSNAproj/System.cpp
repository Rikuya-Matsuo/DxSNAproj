#include "System.h"
#include "Input.h"
#include "SceneBase.h"
#include "ActorBase.h"
#include "SpriteComponent.h"
#include <algorithm>

System::System():
	mPrevCount(GetNowCount()),
	mDeltaTime(0.0f),
	mSpriteSortFlag(false),
	mCurrentScene(nullptr)
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
		//問題発生時にこのかっこの中に入っている
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
		CalculateDeltaTime();

		Input::GetInstance().Update();

		mCurrentScene->Update();

		UpdateActors();

		if (mCurrentScene->GetSceneChangeFlag())
		{
			SceneBase * nextScene = mCurrentScene->GetNextScene();

			if (nextScene != nullptr)
			{
				delete mCurrentScene;

				mCurrentScene = nextScene;
			}
			else
			{
				quitLoop = true;
			}
		}

		if (ProcessMessage() || Input::GetInstance().GetKeyPressDown(KEY_INPUT_ESCAPE))
		{
			quitLoop = true;
		}

		Draw();
	}
}

void System::Finish()
{
	// シーンのメモリ解放
	SceneBase * nextScene = mCurrentScene->GetNextScene();
	if (nextScene != nullptr)
	{
		delete nextScene;
	}
	if (mCurrentScene != nullptr)
	{
		delete mCurrentScene;
	}

	// アクターのメモリ解放
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// スプライトの画像データのメモリ解放
	SpriteComponent::Finish();

	std::vector<ActorBase *>().swap(mActors);
	std::list<SpriteComponent *>().swap(mSprites);

	DxLib_End();
}

void System::CalculateDeltaTime()
{
	int nowCount = GetNowCount();
	mDeltaTime = (nowCount - mPrevCount) / 1000.0f;
	
	// 調整
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
		// ラムダ式
		bool(*drawOrderSort)(const SpriteComponent *, const SpriteComponent *)
			= [](const SpriteComponent * lhs, const SpriteComponent * rhs)
		{
			return lhs->GetDrawOrder() <= rhs->GetDrawOrder();
		};

		mSprites.sort(drawOrderSort);

		mSpriteSortFlag = false;
	}

	for (auto sprite : mSprites)
	{
		sprite->Draw();
	}

	ScreenFlip();
}

void System::UpdateActors()
{
	for (auto member : mActors)
	{
		member->Update();
	}
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

void System::ResisterSprite(const SpriteComponent * sprite)
{
	const int drawOrder = sprite->GetDrawOrder();

	for (auto member : mSprites)
	{
		if (drawOrder > member->GetDrawOrder())
		{
			auto itr = std::find(mSprites.begin(), mSprites.end(), member);

			mSprites.insert(itr, const_cast<SpriteComponent *>(sprite));
			return;
		}
	}

	mSprites.emplace_back(const_cast<SpriteComponent *>(sprite));
}

void System::DeresisterSprite(const SpriteComponent * sprite)
{
	auto itr = std::find(mSprites.begin(), mSprites.end(), const_cast<SpriteComponent *>(sprite));

	if (itr != mSprites.end())
	{
		mSprites.erase(itr);
	}
}
