#pragma once
#include "DxLib.h"

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	void RequestSceneChange() { mFlags |= mSceneChangeFlagMask; }
	bool GetSceneChangeFlag() const { return mFlags & mSceneChangeFlagMask; }

protected:
	typedef UINT8 BitFlag;
	static const BitFlag mSceneChangeFlagMask;

	BitFlag mFlags;

	SceneBase * mNextScene;
};
