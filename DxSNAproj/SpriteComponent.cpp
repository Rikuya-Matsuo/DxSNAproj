#include "SpriteComponent.h"
#include "ActorBase.h"
#include "System.h"

std::unordered_map<std::string, int> SpriteComponent::mHandleDictionaly;

SpriteComponent::SpriteComponent(const ActorBase * owner, int drawOrder):
	ComponentBase(owner, 300),
	mHandle(new int),
	mDrawOrder(drawOrder)
{
}

SpriteComponent::~SpriteComponent()
{
	if (mHandle != nullptr)
	{
		delete mHandle;
	}
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
		*mHandle = LoadGraph(fileName.c_str());

		// �o�^
		mHandleDictionaly[fileName] = *mHandle;
	}

	// �q�b�g�����ꍇ
	else
	{
		// �n���h�����R�s�[
		*mHandle = mHandleDictionaly[fileName];
	}
}

void SpriteComponent::Draw()
{
	if (mOwner->GetVisibleFlag())
	{

	}
}

void SpriteComponent::SetDrawOrder(int value)
{
	mDrawOrder = value;

	System::GetInstance().RequestSortSprites();
}
