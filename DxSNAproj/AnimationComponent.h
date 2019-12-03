#pragma once
#include "SpriteComponent.h"
#include "DivGraphInfo.h"

class Animation;

class AnimationComponent final : public SpriteComponent
{
public:
	AnimationComponent(const ActorBase * owner, int drawOrder = 100);
	~AnimationComponent();

	void Update() override;

	void ResisterLoadAnimation(int index, const DivGraphInfo& info);
	void ResisterLoadAnimation(int index, const std::string& fileName, int allNum, int xNum, int yNum, float width, float height);

	void SetActiveAnimation(int index);

	void SetAnimLoopFlag(bool value) { BitFlagFunc::SetBitByBool(value, mDelivedFlags, mAnimLoopFlagMask); }

	void SetSecondPerFrame(int index, float second);

private:
	typedef UINT8 BitFlag;
	static const BitFlag mChangedScaleFlagMask;
	static const BitFlag mAnimLoopFlagMask;
	static const BitFlag mChangedActiveAnimFlagMask;


	BitFlag mDelivedFlags;

	std::unordered_map<int, Animation *> mAnimations;

	int mActiveAnimationNumber;

	bool GetChangedScaleFlag() const override { return mDelivedFlags & mChangedScaleFlagMask; }
	void SetChangedScaleFlagTrue() override { mDelivedFlags |= mChangedScaleFlagMask; }

	friend void SpriteComponent::Finish();
	//static void Finish();

	bool SearchAnimationByIndex(int index);
};
