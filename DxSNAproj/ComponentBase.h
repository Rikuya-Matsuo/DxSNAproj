#pragma once
#include "DxLib.h"
#include "BitFlagFunc.h"

class ActorBase;

class ComponentBase
{
public:
	ComponentBase(const ActorBase * owner, int priority = 100);
	virtual ~ComponentBase();

	virtual void Update();

	int GetPriority() const { return mPriority; }

	void SetActive(bool value) { BitFlagFunc::SetBitByBool(value, mFlags, mActiveFlag); }
	bool GetActiveFlag() const { return mFlags & mActiveFlag; }

protected:
	typedef UINT8 BitFlag;
	static const BitFlag mActiveFlag;


	BitFlag mFlags;

	ActorBase * mOwner;

	// この値が小さいものが先に処理される。
	int mPriority;
};

