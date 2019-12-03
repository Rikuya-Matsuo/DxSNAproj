#pragma once
#include "ActorBase.h"

class AnimationComponent;

class Player : public ActorBase
{
public:
	Player();
	~Player();

private:
	enum AnimationPattern
	{
		Stay = 0,
		Run,
		JumpUp,
		Landing,
		Damage,
		Cover,
		Invalid_AnimationPattern
	};

	UINT8 mCurrentAnimation;

	AnimationComponent * mAnimComponent;

	float mSpeed;

	void UpdateActor() override;
};
