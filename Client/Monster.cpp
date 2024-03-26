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
		GET_MEMDC, int(lx), int(ly), w, h,
		GetTexture()->GetDC(), 0, 0, w, h, RGB(255, 0, 255)
	);

	ComponentRender();
}

void Monster::Init()
{
	// name
	SetObjectName(L"DefaultMonster");

	// texture
	SetTexture(static_cast<Texture*>(RESOURCE->LoadTexture(L"Player", L"texture\\test_airplane.bmp")));

	// collider
	CreateCollider();
	auto col = GetCollider();
	int th = GetTexture()->GetTexHeight();
	int tw = GetTexture()->GetTexWidth();
	col->SetColliderScale(Vec2(GetScale().x - 10.f, GetScale().y - 10.f));
	col->SetOffset(Vec2(0, 0));
}

void Monster::Begin()
{

}

void Monster::End()
{

}

void Monster::OnCollision(Collider* otherCollider)
{
	
}

void Monster::OnCollisionEnter(Collider* otherCollider)
{
	/*Object* otherObject = otherCollider->GetOuterObject();
	if (otherObject->GetObjectName() == L"DefaultProjectile")
	{
		DeleteObject(this);
	}*/
}

void Monster::OnCollisionExit(Collider* otherCollider)
{

}
