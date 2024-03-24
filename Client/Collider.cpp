#include "pch.h"
#include "Collider.h"
#include "Object.h"

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
	:
	_outerObject(),
	_offset(origin._offset),
	_finalPos(origin._finalPos),
	_colliderScale(origin._colliderScale),
	_id(g_nextID++)
{
	
}

void Collider::FinalUpdate()
{
	Vec2 objPos = GetOuterObject()->GetPos();
	_finalPos = objPos + _offset;

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

	Vec2 scale = GetColliderScale();
	Vec2 finalPos = GetFinalPos();

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

void Collider::OnCollision(Collider* other)
{
	GetOuterObject()->OnCollision(other);
}

void Collider::OnCollisionEnter(Collider* other)
{
	_isCollision++;
	GetOuterObject()->OnCollisionEnter(other);
}

void Collider::OnCollisionExit(Collider* other)
{
	_isCollision--;
	GetOuterObject()->OnCollisionExit(other);
}
