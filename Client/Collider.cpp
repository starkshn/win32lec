#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "Component.h"

UINT Collider::g_nextID = 1;

Collider::Collider()
	:
	_id(g_nextID++)
{
	
}

Collider::~Collider()
{
	
}

Collider::Collider(const Collider& origin)
{
	auto comp = static_cast<Component>(origin);

	SetOwnerObject(nullptr);
	SetOffset(comp.GetOffset());
	SetFinalPos(comp.GetFinalPos());
	SetScale(comp.GetScale());
	SetID(g_nextID++);
}

void Collider::FinalUpdate()
{
	Component::FinalUpdate();

	assert(0 <= _isCollision);
}

void Collider::Render()
{
	if (_isCollision > 0)
	{
		GDI->SetBrush(GET_MEMDC, BRUSH_TYPE::HOLLOW);
		GDI->SetPen(GET_MEMDC, PEN_TYPE::RED);
	}
	else
	{
		GDI->SetBrush(GET_MEMDC, BRUSH_TYPE::HOLLOW);
		GDI->SetPen(GET_MEMDC, PEN_TYPE::GREEN);
	}

	Vec2 scale		= GetScale();
	Vec2 finalPos	= GetFinalPos();

	DRAW_RECT_COLLIDER
	(
		int(finalPos.x - scale.x / 2.f),
		int(finalPos.y - scale.y / 2.f),
		int(finalPos.x + scale.x / 2.f),
		int(finalPos.y + scale.y / 2.f)
	);

	GDI->ReleaseBrush();
	GDI->ReleasePen();
}

void Collider::Init()
{

}

void Collider::OnCollision(Collider* other)
{
	GetOwnerObject()->OnCollision(other);
}

void Collider::OnCollisionEnter(Collider* other)
{
	_isCollision++;
	GetOwnerObject()->OnCollisionEnter(other);
}

void Collider::OnCollisionExit(Collider* other)
{
	_isCollision--;
	GetOwnerObject()->OnCollisionExit(other);
}
