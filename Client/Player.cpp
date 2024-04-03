#include "pch.h"
#include "Player.h"
#include "Projectile.h"
#include "Projectile_Sin.h"
#include "Projectile_Cos.h"
#include "Texture.h"
#include "Collider.h"
#include "Component.h"
#include "Animator.h"
#include "Animation.h"

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
	ComponentRender();
}

void Player::Init()
{
	// get resolution
	auto res = GET_RESOLUTION;

	// set name
	SetObjectName(L"Player");

	// set texture
	// 애니매이션 등장 이후로 직접 Texture를 로드할 필요가 없다
	// SetTexture(static_cast<Texture*>(RESOURCE->LoadTexture(L"Player", L"texture\\test_airplane.bmp")));

	// set pos, scale
	SetPos(Vec2(res.x / 2.f, 500.f));
	SetScale(Vec2(50.f, 50.f));
	
	// ===================================
	// Comp
	// ===================================
	// collider
	Collider* compCollider = CreateComponent<Collider>(COMP_TYPE::COLLIDER);
	int th		= 100;
	int tw		= 100;
	compCollider->SetScale(Vec2(float(th - 30), float(tw - 30)));
	compCollider->SetOffset(Vec2(0, 15));

	// Animator Create
	Animator* compAnimator = CreateComponent<Animator>(COMP_TYPE::ANIMATOR);
	Texture* animRes = static_cast<Texture*>(RESOURCE->LoadTexture(L"PlayerAnim", L"texture\\ZeldaAnimation_Mazenta.bmp"));

	// 120 x 130 
	// 정면 모습 텍스쳐 기준 pos: 0, 520
	// 한 애니매이션당 자를 간격 120, 130
	// anim 간 스텝할(이동하며 자를) 거리 120, 0
	// duration 0.1f
	// 10 Frame


	// 아래 순서대로
	// 1. 애니매이션 생성
	// 2. 생성한 애니매이션 가져오기
	// 3. 현재 current Animation으로 설정 (그래야 PlayAnimation동작함)
	compAnimator->CreateAnimation(Z_WALK_FRONT, animRes, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(120.f, 0), 0.05f, 10);
	Animation* anim = compAnimator->FindAnimation(Z_WALK_FRONT);
	compAnimator->SetCurrentAnim(anim);
	anim->SetAnimLoop(true);

	uint32 _max = anim->GetAnimMaxFrame();
	for (uint32 i = 0; i < _max; ++i)
	{
		AnimFrame& finfo = anim->GetAnimFrame(i);
		finfo._offset = Vec2(0.f, -50.f);
	}
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
