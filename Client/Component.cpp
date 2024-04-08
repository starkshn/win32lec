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
	// 최상단 부모인 Component에서 OwnerObject에 대한 FinalPos를 업데이트 한다.
	Vec2 objPos = GetOwnerObject()->GetPos();
	SetFinalPos(objPos + _offset);

	// 최상단 부모인 Component에서 render할 좌표를 업데이트 해준다.
	SetRenderPos(GetCompRenderPos());
}

void Component::Render()
{
	
}

const Vec2 Component::GetCompRenderPos()
{
	return _renderPos = GetOwnerObject()->GetRenderPos();
}
