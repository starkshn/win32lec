#include "pch.h"
#include "Player.h"
#include "Projectile.h"
#include "Projectile_Sin.h"
#include "Projectile_Cos.h"
#include "Texture.h"
#include "Collider.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Update()
{
	Object::Update();
	DisMovement();
}

void Player::Render()
{
	// DRAW_RECT();

	uint32 h = (int)GetTexture()->GetTexHeight();
	uint32 w = (int)GetTexture()->GetTexWidth();

	Vec2 pos = GetPos();
	int lx = int(pos.x - float(w / 2.f));
	int ly = int(pos.y - float(h / 2.f));

	// BitBlt(GET_MEMDC(), int(lx), int(ly), w, h, GetTexture()->GetDC(), 0, 0, SRCCOPY);

	TransparentBlt
	(
		GET_MEMDC(), int(lx), int(ly), w, h,
		GetTexture()->GetDC(), 0, 0, w, h, RGB(255, 0, 255)
	);

	ComponentRender();
}

void Player::Init()
{
	auto res = GET_RESOLUTION();

	SetPos(Vec2(res.x / 2.f, 500.f));
	SetScale(Vec2(50.f, 50.f));

	// set player texture
	SetTexture(static_pointer_cast<Texture>(RESOURCE->LoadTexture(L"Player", L"texture\\test_airplane.bmp")));
	
	// create collider
	CreateCollider();
	auto col = GetCollider();
	int th = GetTexture()->GetTexHeight();
	int tw = GetTexture()->GetTexWidth();
	col->SetColliderScale(Vec2(float(th - 30), float(tw - 30)));
	col->SetOffset(Vec2(0, 15));
}

void Player::Begin()
{

}

void Player::End()
{

}

void Player::DisMovement()
{
	auto type = SCENE->GetCurrentSceneType();
	switch (type)
	{
	case SCENE_TYPE::MAIN_MENU:
		MoveWASD();
		break;
	case SCENE_TYPE::START:
		AngryMove();
		break;
	case SCENE_TYPE::STAGE_01:
		break;
	case SCENE_TYPE::STAGE_02:
		break;
	case SCENE_TYPE::TOOL:
		break;
	default:
		break;
	}
}

void Player::MoveWASD()
{
	auto pos = GetPos();

	if (KEY_HOLD(KEYES::W))
	{
		pos.y -= 100.f * DT_F;
	}

	if (KEY_HOLD(KEYES::A))
	{
		pos.x -= 100.f * DT_F;
	}

	if (KEY_HOLD(KEYES::S))
	{
		pos.y += 100.f * DT_F;
	}

	if (KEY_HOLD(KEYES::D))
	{
		pos.x += 100.f * DT_F;
	}

	if (KEY_PRESSED(KEYES::SPACE))
	{
		CreateProjectile();
	}

	SetPos(pos);
}

void Player::AngryMove()
{
	
}

void Player::CreateProjectile()
{

	auto proj = GetOuterScene()->SpawnDynamicObject<Projectile>
		(
			OBJ_PROJECTILE,
			DEFAULT_OBJECT_STATE,
			DEFAULT_PROJECTILE_POS,
			DEFAULT_PROJ_SCALE,
			DEFAULT_PROJ_SPEED
		);

	/*auto proj = GetOuterScene()->SpawnDynamicObject<Projectile_Sin>
		(
			OBJ_PROJECTILE,
			DEFAULT_OBJECT_STATE, 
			DEFAULT_PROJECTILE_POS,
			DEFAULT_PROJ_SCALE,
			DEFAULT_PROJ_SPEED
		);*/

	/*GetOuterScene()->SpawnDynamicObject<Projectile_Cos>
		(
			OBJ_PROJECTILE,
			DEFAULT_OBJECT_STATE,
			DEFAULT_PROJECTILE_POS,
			DEFAULT_PROJ_SCALE,
			DEFAULT_PROJ_SPEED
		);*/

	proj->Init();
}
