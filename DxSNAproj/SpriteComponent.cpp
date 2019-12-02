#include "SpriteComponent.h"
#include "ActorBase.h"
#include "System.h"

const SpriteComponent::BitFlag SpriteComponent::mChangedScaleFlagMask = 1 << 0;

std::unordered_map<std::string, int> SpriteComponent::mHandleDictionaly;

SpriteComponent::SpriteComponent(const ActorBase * owner, int drawOrder, bool transFlag):
	ComponentBase(owner, 300),
	mHandle(-1),
	mDrawOrder(drawOrder),
	mTransFlag(transFlag),
	mScale(1.0f),
	mDelivedFlags(0)
{
	System::GetInstance().ResisterSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	System::GetInstance().DeresisterSprite(this);
}

void SpriteComponent::Finish()
{
	std::unordered_map<std::string, int>().swap(mHandleDictionaly);
}

void SpriteComponent::Load(const std::string& fileName)
{
	// ����
	auto itr = mHandleDictionaly.find(fileName);
	
	// �q�b�g���Ȃ������ꍇ
	if (itr == mHandleDictionaly.end())
	{
		// ���[�h
		mHandle = LoadGraph(fileName.c_str());

		// �o�^
		mHandleDictionaly[fileName] = mHandle;
	}

	// �q�b�g�����ꍇ
	else
	{
		// �n���h�����R�s�[
		mHandle = mHandleDictionaly[fileName];
	}

	// �T�C�Y���擾
	GetGraphSizeF(mHandle, &mSize.x, &mSize.y);
}

void SpriteComponent::Update()
{
	if (GetChangedScaleFlag())
	{
		// �摜�T�C�Y���擾������
		GetGraphSizeF(mHandle, &mSize.x, &mSize.y);

		// �T�C�Y�l�𒲐�
		mSize.x *= mScale;
		mSize.y *= mScale;
	}
}

void SpriteComponent::Draw()
{
	if (mOwner->GetVisibleFlag())
	{
		// �`�����p�ӂ���
		Vector2D pos = mOwner->GetPosition();
		Vector2D rightDownPos = pos + mSize;

		DrawExtendGraphF(pos.x, pos.y, rightDownPos.x, rightDownPos.y, mHandle, mTransFlag);
	}
}

void SpriteComponent::SetDrawOrder(int value)
{
	mDrawOrder = value;

	System::GetInstance().RequestSortSprites();
}

void SpriteComponent::SetScale(float extendRate)
{
	mScale = extendRate;

	SetChangedScaleFlagTrue();
}
