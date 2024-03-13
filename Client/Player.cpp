#include "pch.h"
#include "Player.h"

void Player::Update()
{
	auto pos = GetPos();

	if (GET_KEY_STATE(KEYES::W) == KEY_STATE::HOLD)
	{
		pos.y -= 100.f * DT;
	}

	if (GET_KEY_STATE(KEYES::A) == KEY_STATE::HOLD)
	{
		pos.x -= 100.f * DT;
	}

	if (GET_KEY_STATE(KEYES::S) == KEY_STATE::HOLD)
	{
		pos.y += 100.f * DT;
	}

	if (GET_KEY_STATE(KEYES::D) == KEY_STATE::HOLD)
	{
		pos.x += 100.f * DT;
	}

	SetPos(pos);
}

void Player::Render()
{
	Rectangle(GET_MEMDC(), GetLeft(), GetTop(), GetRight(), GetBottom());
}
