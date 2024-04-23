#include "pch.h"
#include "ButtonUI.h"
#include "Scene.h"
#include "Object.h"

ButtonUI::ButtonUI()
{

}

ButtonUI::ButtonUI(const ButtonUI& origin)
    :
    UI(origin),
    _func(origin._func), /*함수 포인터도 복사*/
    _objectMemFunc(origin._objectMemFunc),
    _sceneMemFunc(origin._sceneMemFunc)
{
    Scene* curScene = SCENE->GetCurrentScene();
    curScene->PushBackObjectByType(this, OBJECT_TYPE::UI);

    if (nullptr != origin._objectWhoCallMemFunc)
    {
        _objectWhoCallMemFunc = this;
    }

    if (nullptr != origin._objectWhoCallMemFunc)
    {
        _sceneWhoCallMemFunc = origin._sceneWhoCallMemFunc;
    }

    SetObjectName(L"Copy_ButtonUI");
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
    uint32 textLen = uint32(text.length());
    uint32 offsetIdx = uint32(GetScale().x / textLen);

    TextOut(GET_MEMDC, int32(pos.x + offsetIdx), int32(pos.y + offsetIdx), text.c_str(), uint32(text.length()));
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
    if (nullptr != _func)
    {
        _func(_lparam, _rparam);
    }

    if (_objectWhoCallMemFunc && _objectMemFunc)
    {
        // 조금 더럽다
        ((*_objectWhoCallMemFunc).*_objectMemFunc)();
    }

    if (_sceneWhoCallMemFunc && _sceneMemFunc)
    {
        ((*_sceneWhoCallMemFunc).*_sceneMemFunc)();
    }
}
