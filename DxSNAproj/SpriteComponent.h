#pragma once
#include "DxLib.h"
#include "ComponentBase.h"
#include "Vector.h"
#include <string>
#include <unordered_map>

class SpriteComponent : public ComponentBase
{
public:
	SpriteComponent(const ActorBase * owner, int drawOrder = 100, bool transFlag = true);
	virtual ~SpriteComponent();

	static void Finish();

	void Load(const std::string& fileName);

	void Update() override;

	virtual void Draw();

	void SetDrawOrder(int value);
	int GetDrawOrder() const { return mDrawOrder; }

	void SetScale(float extendRate);

protected:
	int mHandle;

	int mDrawOrder;

	bool mTransFlag;

	Vector2D mSize;

	float mScale;

	virtual bool GetChangedScaleFlag() const { return mDelivedFlags & mChangedScaleFlagMask; }
	virtual void SetChangedScaleFlagTrue() { mDelivedFlags |= mChangedScaleFlagMask; }

private:
	typedef UINT8 BitFlag;
	static const BitFlag mChangedScaleFlagMask;


	BitFlag mDelivedFlags;

	static std::unordered_map<std::string, int> mHandleDictionaly;
};

