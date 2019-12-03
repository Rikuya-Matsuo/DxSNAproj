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
	// ����
	auto itr = mAnimations.find(mActiveAnimationNumber);
	
	// �����Ƀq�b�g
	if (itr != mAnimations.end())
	{
		Animation * activeAnim = mAnimations[mActiveAnimationNumber];

		activeAnim->Update();

		// �n���h�����X�V
		mHandle = activeAnim->GetCurrentFrame();

		// �T�C�Y���擾
		GetGraphSizeF(mHandle, &mSize.x, &mSize.y);
	}

	// ������g����������Ȃ��A�A�N�e�B�u�ȃA�j���[�V�������؂�ւ�������Ƃ������t���O
	if (mDelivedFlags & mChangedActiveAnimFlagMask)
	{
		// ���Ă�������i�΁j
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
	// ���[�h
	Animation * anim = new Animation;
	anim->Load(fileName, allNum, xNum, yNum, width, height);

	// �w�肳�ꂽ�ԍ��œo�^
	mAnimations[index] = anim;

	// �Ō�Ƀ��[�h���ꂽ���̂��A�N�e�B�u�Ƃ���
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
