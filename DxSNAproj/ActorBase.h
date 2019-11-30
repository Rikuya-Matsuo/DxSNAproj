#pragma once
#include "DxLib.h"
#include "Vector.h"
#include "BitFlagFunc.h"
#include <list>

class ComponentBase;

class ActorBase
{
public:
	ActorBase();
	virtual ~ActorBase();

	// �R���|�[�l���g�o�^
	void ResisterComponent(const ComponentBase * cmp);
	// �R���|�[�l���g�o�^����
	void DeresisterComponent(const ComponentBase * cmp);

	void SetPosition(const Vector2D & pos) { mPosition = pos; }
	const Vector2D& GetPosition() const { return mPosition; }

	void SetBeyondSceneFlag(bool value) { BitFlagFunc::SetBitByBool(value, mFlags, mBeyondSceneFlagMask); }
	bool GetBeyondSceneFlag() const { return mFlags & mBeyondSceneFlagMask; }

	void SetVisible(bool value) { BitFlagFunc::SetBitByBool(!value, mFlags, mInvisibleFlagMask); }
	bool GetVisibleFlag() const { return !(mFlags & mInvisibleFlagMask); }

protected:
	typedef UINT8 BitFlag;
	static const BitFlag mBeyondSceneFlagMask;
	static const BitFlag mInvisibleFlagMask;

	BitFlag mFlags;

	Vector2D mPosition;

	std::list<ComponentBase *> mComponents;
};
