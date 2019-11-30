#include "ActorBase.h"
#include "ComponentBase.h"

const ActorBase::BitFlag ActorBase::mBeyondSceneFlagMask = 1 << 0;
const ActorBase::BitFlag ActorBase::mInvisibleFlagMask = 1 << 1;

ActorBase::ActorBase():
	mFlags(0),
	mPosition(0.0f, 0.0f)
{
}

ActorBase::~ActorBase()
{
}

void ActorBase::ResisterComponent(const ComponentBase * cmp)
{
	const int priority = cmp->GetPriority();

	bool inserted = false;
	for (auto member : mComponents)
	{
		if (priority >= member->GetPriority())
		{
			auto insertPoint = std::find(mComponents.begin(), mComponents.end(), member);
			mComponents.insert(insertPoint, const_cast<ComponentBase*>(cmp));
			inserted = true;
		}
	}

	if (!inserted)
	{
		mComponents.emplace_back(const_cast<ComponentBase*>(cmp));
	}
}

void ActorBase::DeresisterComponent(const ComponentBase * cmp)
{
	auto itr = std::find(mComponents.begin(), mComponents.end(), cmp);

	if (itr != mComponents.end())
	{
		mComponents.erase(itr);
	}
}
