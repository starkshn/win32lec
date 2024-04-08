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
}

void Monster::Render()
{
	Object::Render();

	uint32 h = (int)GetTexture()->GetTexHeight();
	uint32 w = (int)GetTexture()->GetTexWidth();

	Vec2 pos = GetPos();
	Vec2 renderPos = GetRenderPos();
	/*int lx = int(pos.x - float(w / 2.f));
	int ly = int(pos.y - float(h / 2.f));*/

	int lx = int(renderPos.x - float(w / 2.f));
	int ly = int(renderPos.y - float(h / 2.f));

	TransparentBlt
	(
		GET_MEMDC, 
		int(lx), int(ly), w, h,
		GetTexture()->GetDC(), 
		0, 0, w, h, 
		RGB(255, 0, 255)
	);
}

void Monster::Init()
{
	// name
	SetObjectName(L"DefaultMonster");

	// texture
	SetTexture(static_cast<Texture*>(RESOURCE->LoadTexture(L"Player", L"texture\\test_airplane.bmp")));

	// collider
	Component* comp = CreateComponent<Collider>(COMP_TYPE::COLLIDER);
	int th = GetTexture()->GetTexHeight();
	int tw = GetTexture()->GetTexWidth();
	comp->SetScale(Vec2(GetScale().x - 10.f, GetScale().y - 10.f));
	comp->SetOffset(Vec2(0, 0));
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
	
}

void Monster::OnCollisionExit(Collider* otherCollider)
{

}
