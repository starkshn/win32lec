#include "pch.h"
#include "Monster.h"
#include "Texture.h"
#include "Collider.h"

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
	uint32 h = (int)GetTexture()->GetTexHeight();
	uint32 w = (int)GetTexture()->GetTexWidth();

	Vec2 pos = GetPos();
	int lx = int(pos.x - float(w / 2.f));
	int ly = int(pos.y - float(h / 2.f));

	TransparentBlt
	(
		GET_MEMDC(), int(lx), int(ly), w, h,
		GetTexture()->GetDC(), 0, 0, w, h, RGB(255, 0, 255)
	);

	ComponentRender();
	// Rectangle(GET_MEMDC(), GetLeft(), GetTop(), GetRight(), GetBottom());
}

void Monster::Init()
{
	// set player texture
	SetTexture(static_pointer_cast<Texture>(RESOURCE->LoadTexture(L"Player", L"texture\\test_airplane.bmp")));




	// create collider
	CreateCollider();
	auto col = GetCollider();
	int th = GetTexture()->GetTexHeight();
	int tw = GetTexture()->GetTexWidth();
	col->SetColliderScale(Vec2(th, tw));
	col->SetOffset(Vec2(0, 0));
}

void Monster::Begin()
{

}

void Monster::End()
{

}
