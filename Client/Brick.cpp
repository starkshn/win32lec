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
	Rectangle(GET_MEMDC(), GetLeft(), GetTop(), GetRight(), GetBottom());
}

double gdiv = 2;

void Brick::Init()
{
	auto res = GET_RESOLUTION();
	float radius = (res.x / gdiv) - GetScale().x / 2;
	_radius = radius;
	SetPos(Vec2(GetPos().x + _radius, res.y / 2));
	gdiv += 0.5;
}
