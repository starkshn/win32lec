#include "pch.h"
#include "ButtonUI.h"

ButtonUI::ButtonUI()
{

}

ButtonUI::ButtonUI(const ButtonUI& origin)
    :
    UI(origin)
{
    Scene* curScene = SCENE->GetCurrentScene();
    curScene->PushBackObjectByType(this, OBJECT_TYPE::UI);
}

ButtonUI::~ButtonUI()
{

}

ButtonUI* ButtonUI::Clone()
{
    return new ButtonUI(*this);
}

void ButtonUI::EVENT_MOUSE_HOVERON_UI()
{

}

void ButtonUI::EVENT_MOUSE_LBTN_DOWN_UI()
{

}

void ButtonUI::EVENT_MOUSE_LBTN_UP_UI()
{

}

void ButtonUI::EVENT_MOUSE_LBTN_CLICK_UI()
{

}
