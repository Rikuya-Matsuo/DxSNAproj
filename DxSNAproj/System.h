#pragma once
#include "DxLib.h"
#include "Vector.h"
#include <vector>
#include <list>

class ActorBase;
class SceneBase;
class SpriteComponent;

class System final
{
public:
	~System();

	static System & GetInstance()
	{
		static System instance;
		return instance;
	}

	bool Init(bool windowModeFlag, float width = 1920.0f, float height = 1080.0f);

	void Run();

	void Finish();

	void SetScene(SceneBase * nextScene) { mCurrentScene = nextScene; }

	float GetDeltaTime() const { return mDeltaTime; }

	void ResisterActor(const ActorBase * actor);

	void DeresisterActor(const ActorBase * actor);

	void RequestSortSprites() { mSpriteSortFlag = true; }

private:
	System();

	Vector2D mWindowSize;

	SceneBase * mCurrentScene;

	std::vector<ActorBase *> mActors;

	std::list<SpriteComponent *> mSprites;

	int mPrevCount;

	float mDeltaTime;

	bool mSpriteSortFlag;

	void CalculateDeltaTime();

	void Draw();
};
