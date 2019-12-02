#include "ActorBase.h"
#include "System.h"
#include "ComponentBase.h"
#include <algorithm>

const ActorBase::BitFlag ActorBase::mBeyondSceneFlagMask = 1 << 0;
const ActorBase::BitFlag ActorBase::mInvisibleFlagMask = 1 << 1;
const ActorBase::BitFlag ActorBase::mComponentSortFlagMask = 1 << 2;

ActorBase::ActorBase():
	mFlags(0),
	mPosition(0.0f, 0.0f)
{
	System::GetInstance().ResisterActor(this);
}

ActorBase::~ActorBase()
{
	System::GetInstance().DeresisterActor(this);
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

void ActorBase::Update()
{
	UpdateComponent();

	UpdateActor();
}

void ActorBase::UpdateActor()
{
}

void ActorBase::UpdateComponent()
{
	// コンポーネントのソートが要請されたときはソートする。
	if (mFlags & mComponentSortFlagMask)
	{
		SortComponents();

		// フラグを下す
		mFlags &= ~mComponentSortFlagMask;
	}

	for (auto component : mComponents)
	{
		component->Update();
	}
}

void ActorBase::SortComponents()
{
	bool(*priorityOrder)(const ComponentBase * lhs, const ComponentBase * rhs)
		= [](const ComponentBase * lhs, const ComponentBase * rhs)
	{
		return lhs->GetPriority() <= rhs->GetPriority();
	};

	mComponents.sort(priorityOrder);
}
