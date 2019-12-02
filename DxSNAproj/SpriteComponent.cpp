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
	// 検索
	auto itr = mHandleDictionaly.find(fileName);
	
	// ヒットしなかった場合
	if (itr == mHandleDictionaly.end())
	{
		// ロード
		mHandle = LoadGraph(fileName.c_str());

		// 登録
		mHandleDictionaly[fileName] = mHandle;
	}

	// ヒットした場合
	else
	{
		// ハンドルをコピー
		mHandle = mHandleDictionaly[fileName];
	}

	// サイズを取得
	GetGraphSizeF(mHandle, &mSize.x, &mSize.y);
}

void SpriteComponent::Update()
{
	if (GetChangedScaleFlag())
	{
		// 画像サイズを取得し直す
		GetGraphSizeF(mHandle, &mSize.x, &mSize.y);

		// サイズ値を調整
		mSize.x *= mScale;
		mSize.y *= mScale;
	}
}

void SpriteComponent::Draw()
{
	if (mOwner->GetVisibleFlag())
	{
		// 描画情報を用意する
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
