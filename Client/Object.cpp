#include "pch.h"
#include "Object.h"

Object::Object()
{

}

Object::~Object()
{
}

void Object::Update()
{
	auto pos = GetPos();

	if (GET_KEY_STATE(KEY::W) == KEY_STATE::HOLD)
	{
		pos.y -= 100.f * DT;
	}

	if (GET_KEY_STATE(KEY::A) == KEY_STATE::HOLD)
	{
		pos.x -= 100.f * DT;
	}

	if (GET_KEY_STATE(KEY::S) == KEY_STATE::HOLD)
	{
		pos.y += 100.f * DT;
	}

	if (GET_KEY_STATE(KEY::D) == KEY_STATE::HOLD)
	{
		pos.x += 100.f * DT;
	}

	SetPos(pos);
}

void Object::Render()
{
	Rectangle(GET_MEMDC(), GetLeft(), GetTop(), GetRight(), GetBottom());
}
