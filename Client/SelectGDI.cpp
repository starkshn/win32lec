#include "pch.h"
#include "SelectGDI.h"

SelectGDI::SelectGDI()
{
	
}

SelectGDI::~SelectGDI()
{

}

void SelectGDI::SetBrush(HDC dc, BRUSH_TYPE type)
{
	HBRUSH brush = CORE->GetBrush(type);
	_defaultBrush = (HBRUSH)SelectObject(GET_MEMDC, brush);
}

void SelectGDI::SetPen(HDC dc, PEN_TYPE type)
{
	HPEN greenPen = CORE->GetPen(type);
	_defaultPen = (HPEN)SelectObject(GET_MEMDC, greenPen);
}

void SelectGDI::ReleaseBrush()
{
	SelectObject(GET_MEMDC, _defaultBrush);
}

void SelectGDI::ReleasePen()
{
	SelectObject(GET_MEMDC, _defaultPen);
}
