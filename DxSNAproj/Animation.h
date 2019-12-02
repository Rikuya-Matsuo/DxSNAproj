#pragma once
#include "DxLib.h"
#include <string>
#include <unordered_map>

class Animation
{
public:
	Animation();
	~Animation();

	void Load(const std::string& fileName, int allNum, int xNum, int yNum, float width, float height);

	void Update();

	void Reset();

	int GetCurrentFrame() const { return mHandle[mCurrentFrameNumber]; }

	UINT8 GetFrameMass() const { return mFrameMass; }

	bool GetAnimEndFlag() const { return mFlags & mAnimEndFlagMask; }

	void SetSecondPerFrame(float value) { mSecondPerFrame = value; }

private:
	typedef UINT8 BitFlag;
	static const BitFlag mAnimEndFlagMask;


	BitFlag mFlags;

	int * mHandle;

	UINT8 mFrameMass;

	float mSecondPerFrame;

	float mTimer;

	UINT8 mCurrentFrameNumber;
};
