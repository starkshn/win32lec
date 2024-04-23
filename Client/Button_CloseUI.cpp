#include "pch.h"
#include "Button_CloseUI.h"

Button_CloseUI::Button_CloseUI()
{

}

Button_CloseUI::Button_CloseUI(const Button_CloseUI& origin)
	:
	ButtonUI(origin)
{
	SetTexture(RESOURCE->GetTexture(L"CloseUI", L"CloseUI,bmp"));
	SetObjectName(L"Copy_CloseUI");
}

Button_CloseUI::~Button_CloseUI()
{
	
}

Button_CloseUI* Button_CloseUI::Clone()
{
	return new Button_CloseUI(*this);
}

void Button_CloseUI::CloseThisUI()
{
	this->SetVisible(false);
	this->SetMouseHoverOnThisObject(false);
}
