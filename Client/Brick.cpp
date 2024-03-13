#include "pch.h"
#include "Brick.h"

Brick::Brick()
{
	SetSpeed(200.f);
	SetPos(Vec2{ float(GET_RESOLUTION().x), float(GET_RESOLUTION().y) });
}

Brick::~Brick()
{
	
}

void Brick::Update()
{
	
}

void Brick::Render()
{
	Rectangle(GET_MEMDC(), GetLeft(), GetTop(), GetRight(), GetBottom());
}
