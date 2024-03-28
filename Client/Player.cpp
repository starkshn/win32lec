#include "pch.h"
#include "Player.h"
#include "Projectile.h"
#include "Projectile_Sin.h"
#include "Projectile_Cos.h"
#include "Texture.h"
#include "Collider.h"
#include "Component.h"

Player::Player()
{

}

Player::~Player()
{

}

Player* Player::Clone()
{
	return new Player(*this);
}

void Player::Update()
{
	Object::Update();
	DisMovement();
}

void Player::Render()
{
	uint32 h = (int)GetTexture()->GetTexHeight();
	uint32 w = (int)GetTexture()->GetTexWidth();

	Vec2 pos = GetPos();
	int lx = int(pos.x - float(w / 2.f));
	int ly = int(pos.y - float(h / 2.f));

	// Texture의 모든 생각 다 복붙
	// BitBlt(GET_MEMDC(), int(lx), int(ly), w, h, GetTexture()->GetDC(), 0, 0, SRCCOPY);

	// 마젠타 색상 설정하여 마젠타 색상 제외하고 복붙해주는 함수
	TransparentBlt
	(
		GET_MEMDC, int(lx), int(ly), w, h,
		GetTexture()->GetDC(), 0, 0, w, h, RGB(255, 0, 255)
	);

	ComponentRender();
}

void Player::Init()
{
	// get resolution
	auto res = GET_RESOLUTION;

	// set name
	SetObjectName(L"Player");

	// set texture
	SetTexture(static_cast<Texture*>(RESOURCE->LoadTexture(L"Player", L"texture\\test_airplane.bmp")));

	// set pos, scale
	SetPos(Vec2(res.x / 2.f, 500.f));
	SetScale(Vec2(50.f, 50.f));
	
	// create comp

	// collider
	Component* comp = CreateComponent<Collider>(COMP_TYPE::COLLIDER);
	int th		= GetTexture()->GetTexHeight();
	int tw		= GetTexture()->GetTexWidth();
	comp->SetScale(Vec2(float(th - 30), float(tw - 30)));
	comp->SetOffset(Vec2(0, 15));
	comp->SetVisible();
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

// TODO
void Player::CreateProjectile()
{
	// None Template
	 Object* proj = new Projectile_Sin();
	 CreateObject(proj, OBJECT_TYPE::PROJ_PLAYER);

	// Template (Test) -> 일단 ㄴㄴ
	// CreateObject<Projectile>(OBJECT_TYPE::PROJ_PLAYER);

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
