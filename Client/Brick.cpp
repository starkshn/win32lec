#include "pch.h"
#include "Brick.h"

Brick::Brick()
{
	
}

Brick::~Brick()
{
	
}

void Brick::Update()
{
	Object::Update();

	if (GetProperty() != OBJECT_PROPERTY::STATIC)
	{
		switch (GetRotateType())
		{
			case ROTATE_TYPE::CIRCLE:
			{
				Rotate(_radius);
			}
		default:
			{

			}
			break;
		}
	}
}

void Brick::Render()
{
	DRAW_RECT();
}

void Brick::Init()
{
	float gdiv = 2.f;

	auto res = GET_RESOLUTION;
	float radius = ((res.x / gdiv) - GetScale().x / 2.f);
	_radius = radius;
	SetPos(Vec2(GetPos().x + _radius, (res.y / 2.f)));
	gdiv += 0.5;
}
