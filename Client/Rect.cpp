#include "pch.h"
#include "Rect.h"

Rect::Rect()
{
}

Rect::~Rect()
{
}

void Rect::Update()
{

}

void Rect::Render()
{
	Rectangle(GET_MEMDC, GetLeft(), GetTop(), GetRight(), GetBottom());
}
