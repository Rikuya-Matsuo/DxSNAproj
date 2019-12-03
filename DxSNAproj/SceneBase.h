#pragma once
#include "DxLib.h"

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	SceneBase * GetNextScene() const { return mNextScene; }

	void RequestSceneChange() { mFlags |= mSceneChangeFlagMask; }
	bool GetSceneChangeFlag() const { return mFlags & mSceneChangeFlagMask; }

	virtual void Update() = 0;

protected:
	typedef UINT8 BitFlag;
	static const BitFlag mSceneChangeFlagMask;

	BitFlag mFlags;

	SceneBase * mNextScene;
};
