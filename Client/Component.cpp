#include "pch.h"
#include "Component.h"
#include "Object.h"

Component::Component()
{

}

Component::~Component()
{

}

Component::Component(const Component& other)
{
	GDI->SetBrush(GET_MEMDC, BRUSH_TYPE::HOLLOW);
	GDI->SetPen(GET_MEMDC, PEN_TYPE::BLUE);

	Vec2 scale = GetScale();
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

void Component::Update()
{
	// �ֻ�� �θ��� Component���� OwnerObject�� ���� FinalPos�� ������Ʈ �Ѵ�.
	Vec2 objPos = GetOwnerObject()->GetPos();
	SetFinalPos(objPos + _offset);

	// �ֻ�� �θ��� Component���� render�� ��ǥ�� ������Ʈ ���ش�.
	SetRenderPos(GetCompRenderPos());
}

void Component::Render()
{
	
}

const Vec2 Component::GetCompRenderPos()
{
	return _renderPos = GetOwnerObject()->GetRenderPos();
}
