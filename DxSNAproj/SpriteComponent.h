#pragma once
#include "DxLib.h"
#include "ComponentBase.h"
#include <string>
#include <unordered_map>

class SpriteComponent : public ComponentBase
{
public:
	SpriteComponent(const ActorBase * owner, int drawOrder = 100);
	virtual ~SpriteComponent();

	static void Finish();

	void Load(const std::string& fileName);

	virtual void Draw();

	void SetDrawOrder(int value);
	int GetDrawOrder() const { return mDrawOrder; }

protected:
	static std::unordered_map<std::string, int> mHandleDictionaly;

	int * mHandle;

	int mDrawOrder;
};

