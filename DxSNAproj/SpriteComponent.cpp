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
	// 検索
	auto itr = mHandleDictionaly.find(fileName);
	
	// ヒットしなかった場合
	if (itr == mHandleDictionaly.end())
	{
		// ロード
		*mHandle = LoadGraph(fileName.c_str());

		// 登録
		mHandleDictionaly[fileName] = *mHandle;
	}

	// ヒットした場合
	else
	{
		// ハンドルをコピー
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
