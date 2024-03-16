#include "pch.h"
#include "Monster.h"

Monster::Monster()
{

}

Monster::~Monster()
{

}


void Monster::Update()
{
	Object::Update();

	if (GetProperty() != OBJECT_PROPERTY::STATIC)
	{
		Patrol_Vetical_Horizaon_Sin();
	}
}

void Monster::Render()
{
	Rectangle(GET_MEMDC(), GetLeft(), GetTop(), GetRight(), GetBottom());
}

void Monster::Init()
{
	
}

void Monster::Begin()
{
}

void Monster::End()
{
}
