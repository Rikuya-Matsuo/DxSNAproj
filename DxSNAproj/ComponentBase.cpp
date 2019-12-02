#include "ComponentBase.h"
#include "ActorBase.h"

const ComponentBase::BitFlag ComponentBase::mActiveFlag = 1 << 0;

ComponentBase::ComponentBase(const ActorBase * owner, int priority):
	mOwner(const_cast<ActorBase*>(owner)),
	mFlags(mActiveFlag),
	mPriority(priority)
{
	mOwner->ResisterComponent(this);
}


ComponentBase::~ComponentBase()
{
	mOwner->DeresisterComponent(this);
}

void ComponentBase::Update()
{
}
