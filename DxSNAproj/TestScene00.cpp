#include "TestScene00.h"
#include "Player.h"

TestScene00::TestScene00()
{
	Player * p = new Player;
	p->SetPosition(Vector2D::zero);
}


TestScene00::~TestScene00()
{
}

void TestScene00::Update()
{
}
