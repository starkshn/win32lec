#include "pch.h"
#include "UI.h"
#include "Texture.h"

UI::UI()
{

}

UI::~UI()
{
    // TODO Delete UI
    // DeleteObjectsSafe(_vecInnerUI);
}

Object* UI::Clone()
{
    return nullptr;
}

void UI::Update()
{
    // TODO My job
    UpdateInnerUI();
}

void UI::FinalUpdate()
{
    // Todo MY Job
    Object::FinalUpdate();
    
    if (UI* outerUI = GetOuterUI())
    {
        Vec2 outerUIFinalPos = outerUI->GetUIFinalPos();
        Vec2 offset = GetUIOffSet();
        SetUIFinalPos(outerUIFinalPos + offset);
    }
    else
    {
        // outer UI없는 경우 현재 offset이 최종 위치가 된다.
        SetUIFinalPos(GetPos() + GetUIOffSet());
    }
    
    // Final Update InnerUI
    FinalUpdateInnerUI();
}

void UI::Render()
{
    // 마우스 호버체크
    CheckMouseHoverOnUI();

    // TODO My job
    Vec2 pos    = GetUIFinalPos();
    Vec2 scale  = GetScale();

    if (GetThisUIAffectByCamera())
    {
        pos = CAMERA->GetRenderPosFromWindowActualPos(pos);
    }

    if (GetLBTNDownOnThisUI())
    {
        GDI->SetPen(GET_MEMDC, PEN_TYPE::RED);

        Rectangle
        (
            GET_MEMDC,
            int32(pos.x), int32(pos.y),
            int32(pos.x + scale.x),
            int32(pos.y + scale.y)
        );

        GDI->ReleasePen();
    }
    else 
    {
        Rectangle
        (
            GET_MEMDC,
            int32(pos.x), int32(pos.y),
            int32(pos.x + scale.x),
            int32(pos.y + scale.y)
        );
    }

    if (nullptr != GetTexture())
    {
        uint32 h = (int)GetTexture()->GetTexHeight();
        uint32 w = (int)GetTexture()->GetTexWidth();

        Vec2 pos = GetPos();
        Vec2 renderPos = GetUIFinalPos();

        int lx = int(renderPos.x);
        int ly = int(renderPos.y);

        TransparentBlt
        (
            GET_MEMDC,
            int(lx), int(ly), w, h,
            GetTexture()->GetDC(),
            0, 0, w, h,
            RGB(255, 0, 255)
        );
    }
    
    // Render Inner UI
    RenderInnerUI();


}

void UI::Init()
{
    wstring objName = GetObjectName();
    if (objName == L"innerUI_ObjectFaceUI")
    {
        SetTexture(static_cast<Texture*>(RESOURCE->LoadTexture(L"ObjectFace", L"texture\\Carrier_Test.bmp")));
    }
}

void UI::Begin()
{
}

void UI::End()
{
}

void UI::UpdateInnerUI()
{
    for (auto innerUI : _vecInnerUI)
    {
       if (nullptr != innerUI)
            innerUI->Update();
    }
}

void UI::RenderInnerUI()
{
    for (auto innerUI : _vecInnerUI)
    {
        if (nullptr != innerUI)
            innerUI->Render();
    }
}

void UI::FinalUpdateInnerUI()
{
    for (auto innerUI : _vecInnerUI)
    {
        if (nullptr != innerUI)
            innerUI->FinalUpdate();
    }
}

void UI::CheckMouseHoverOnUI()
{
    Vec2 curMousePos = GET_MOUSE_POS;
    if (GetThisUIAffectByCamera())
    {
        curMousePos = CAMERA->GetWindowActualPosFromRenderPos(curMousePos);
    }
    
    Vec2 UIFinalPos = GetUIFinalPos();
    Vec2 UIScale = GetScale();

    if ((UIFinalPos.x <= curMousePos.x && curMousePos.x <= UIFinalPos.x + UIScale.x) &&
        (UIFinalPos.y <= curMousePos.y && curMousePos.y <= UIFinalPos.y + UIScale.y))
    {
        SetMouseHoverOnThisUI(true);
    }
    else
    {
        SetMouseHoverOnThisUI(false);
    }
}

void UI::EVENT_MOUSE_HOVERON_UI()
{
    int a = 10;
}

void UI::EVENT_MOUSE_LBTN_DOWN_UI()
{
    int a = 10;
}

void UI::EVENT_MOUSE_LBTN_UP_UI()
{
    int a = 10;
}

void UI::EVENT_MOUSE_LBTN_CLICK_UI()
{
    int a = 10;
}
