#include "pch.h"
#include "ButtonUI.h"

ButtonUI::ButtonUI()
{

}

ButtonUI::ButtonUI(const ButtonUI& origin)
    :
    UI(origin),
    _func(origin._func) /*함수 포인터도 복사*/
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

void ButtonUI::Render()
{
    UI::Render();

    if (GetVisible() == false) return;
    Vec2 pos = GetUIFinalPos();
    wstring text = GetButtonText();

    TextOut(GET_MEMDC, int32(pos.x + GetScale().x / 2 - 10), int32(pos.y + GetScale().y / 2.f - 10.f), text.c_str(), uint32(text.length()));
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
    if (nullptr == _func) return;
    _func(_lparam, _rparam);
}
