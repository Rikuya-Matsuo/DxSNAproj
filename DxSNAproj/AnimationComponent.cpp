#include "AnimationComponent.h"
#include "Animation.h"

const AnimationComponent::BitFlag AnimationComponent::mChangedScaleFlagMask = 1 << 0;
const AnimationComponent::BitFlag AnimationComponent::mAnimLoopFlagMask = 1 << 1;
const AnimationComponent::BitFlag AnimationComponent::mChangedActiveAnimFlagMask = 1 << 2;

AnimationComponent::AnimationComponent(const ActorBase * owner, int drawOrder):
	SpriteComponent(owner, drawOrder),
	mDelivedFlags(mAnimLoopFlagMask),
	mActiveAnimationNumber(-1)
{
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::Update()
{
	// 検索
	auto itr = mAnimations.find(mActiveAnimationNumber);
	
	// 検索にヒット
	if (itr != mAnimations.end())
	{
		Animation * activeAnim = mAnimations[mActiveAnimationNumber];

		activeAnim->Update();

		// ハンドルを更新
		mHandle = activeAnim->GetCurrentFrame();

		// サイズを取得
		GetGraphSizeF(mHandle, &mSize.x, &mSize.y);
	}

	// いずれ使うかもしれない、アクティブなアニメーションが切り替わったことを示すフラグ
	if (mDelivedFlags & mChangedActiveAnimFlagMask)
	{
		// ついてたら消す（笑）
		mDelivedFlags &= ~mChangedActiveAnimFlagMask;
	}

	SpriteComponent::Update();
}

void AnimationComponent::ResisterLoadAnimation(int index, const DivGraphInfo & info)
{
	ResisterLoadAnimation(index, info.fileName, info.frameMass, info.xNum, info.yNum, info.size.x, info.size.y);
}

void AnimationComponent::ResisterLoadAnimation(int index, const std::string & fileName, int allNum, int xNum, int yNum, float width, float height)
{
	// ロード
	Animation * anim = new Animation;
	anim->Load(fileName, allNum, xNum, yNum, width, height);

	// 指定された番号で登録
	mAnimations[index] = anim;

	// 最後にロードされたものをアクティブとする
	mActiveAnimationNumber = index;
}

void AnimationComponent::SetActiveAnimation(int index)
{
	if (mActiveAnimationNumber != index)
	{
		mDelivedFlags |= mChangedActiveAnimFlagMask;
	}

	mActiveAnimationNumber = index;
}

void AnimationComponent::SetSecondPerFrame(int index, float second)
{
	if (SearchAnimationByIndex(index))
	{
		mAnimations[index]->SetSecondPerFrame(second);
	}
}

bool AnimationComponent::SearchAnimationByIndex(int index)
{
	bool ret = false;
	auto itr = mAnimations.find(index);

	if (itr != mAnimations.end())
	{
		ret = true;
	}

	return ret;
}
