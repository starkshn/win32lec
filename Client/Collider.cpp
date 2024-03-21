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

void Collider::FinalUpdate()
{
	Vec2 objPos = GetOuterObject()->GetPos();
	_finalPos = objPos + _offset;
}

void Collider::Render()
{
	GDI->SetBrush(GET_MEMDC(), BRUSH_TYPE::HOLLOW);
	GDI->SetPen(GET_MEMDC(), PEN_TYPE::GREEN);

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
