#include "SceneBase.h"
#include <cstdlib>

const SceneBase::BitFlag SceneBase::mSceneChangeFlagMask = 1 << 0;

SceneBase::SceneBase():
	mFlags(0),
	mNextScene(nullptr)
{
	
}

SceneBase::~SceneBase()
{
}
