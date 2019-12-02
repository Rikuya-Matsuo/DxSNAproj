#include "Animation.h"
#include "System.h"

const Animation::BitFlag Animation::mAnimEndFlagMask = 1 << 0;

Animation::Animation():
	mFrameMass(0),
	mCurrentFrameNumber(0),
	mSecondPerFrame(1.0f / 60),
	mTimer(0.0f)
{
}

Animation::~Animation()
{
	for (int i = 0; i < mFrameMass; ++i)
	{
		DeleteGraph(mHandle[i]);
	}

	delete[] mHandle;
}

void Animation::Load(const std::string & fileName, int allNum, int xNum, int yNum, float width, float height)
{
	mFrameMass = allNum;

	mHandle = new int[mFrameMass];

	LoadDivGraphF(fileName.c_str(), allNum, xNum, yNum, width, height, mHandle);
}

void Animation::Update()
{
	mTimer = System::GetInstance().GetDeltaTime();

	// 1ループ完遂フラグを下す
	mFlags &= ~mAnimEndFlagMask;

	// 1コマあたりの秒数を経過したとき
	if (mTimer >= mSecondPerFrame)
	{
		if (++mCurrentFrameNumber >= mFrameMass)
		{
			mCurrentFrameNumber = 0;

			// アニメーションが1ループ終えたことを示すフラグを立てる
			mFlags |= mAnimEndFlagMask;
		}

		// タイマーリセット
		mTimer = 0.0f;
	}
}

void Animation::Reset()
{
	mCurrentFrameNumber = 0;
	mTimer = 0.0f;
}
