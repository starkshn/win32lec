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

void Collider::Update()
{
	Component::Update();

	assert(0 <= _isCollision);
}

void Collider::Render()
{
	Component::Render();

	SelectBrushAndPenColor();

	Vec2 scale		= GetScale();
	Vec2 renderPos	= GetRenderPos();

	DRAW_RECT_COLLIDER
	(
		int(renderPos.x - scale.x / 2.f),
		int(renderPos.y - scale.y / 2.f),
		int(renderPos.x + scale.x / 2.f),
		int(renderPos.y + scale.y / 2.f)
	);

	RollBackBrushAndPenColor();
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

void Collider::SelectBrushAndPenColor()
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
}

void Collider::RollBackBrushAndPenColor()
{
	GDI->ReleaseBrush();
	GDI->ReleasePen();
}
