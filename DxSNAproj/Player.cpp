#include "Player.h"
#include "System.h"
#include "Input.h"
#include "AnimationComponent.h"

Player::Player():
	mCurrentAnimation(AnimationPattern::Stay),
	mSpeed(System::GetInstance().GetWindowSize().x / 2.0f)
{
	mAnimComponent = new AnimationComponent(this);
	DivGraphInfo divGraph;
	// 待機状態アニメのロード
	{
		divGraph.fileName = "Resource/Image/Player/Test.png";
		divGraph.frameMass = 3;
		divGraph.xNum = 3;
		divGraph.yNum = 1;
		divGraph.size = Vector2D(32, 40);
		mAnimComponent->ResisterLoadAnimation(AnimationPattern::Stay, divGraph);

		mAnimComponent->SetSecondPerFrame(AnimationPattern::Stay, 0.5f);
		mAnimComponent->SetScale(1.5f);
	}
}

Player::~Player()
{
}

void Player::UpdateActor()
{
	float speed = mSpeed * System::GetInstance().GetDeltaTime();
	if (Input::GetInstance().GetKeyPressed(KEY_INPUT_RIGHT))
	{
		mPosition.x += speed;
	}
	if (Input::GetInstance().GetKeyPressed(KEY_INPUT_LEFT))
	{
		mPosition.x -= speed;
	}

	if (Input::GetInstance().GetKeyPressed(KEY_INPUT_UP))
	{
		mPosition.y -= speed;
	}
	if (Input::GetInstance().GetKeyPressed(KEY_INPUT_DOWN))
	{
		mPosition.y += speed;
	}
}
