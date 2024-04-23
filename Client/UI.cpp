#include "pch.h"
#include "UI.h"
#include "Texture.h"
#include "Object.h"
#include "Scene.h"

UI::UI()
{

}

UI::~UI()
{
    
}

UI::UI(const UI& origin)
    :
    Object(origin),
    _outerUI(nullptr),
    _offset(origin._offset),
    _finalPos(origin._finalPos),
    _affectByCameraPos(origin._affectByCameraPos),
    _mouseHoverOn(false),
    _lbtnDownOnThisUI(false)
{
    SetOuterScene(const_cast<UI&>(origin).GetOuterScene());
    SetOuterSceneType(const_cast<UI&>(origin).GetOuterSceneType());
    SetTexture(nullptr);
    SetObjectName(const_cast<UI&>(origin).GetObjectName());
    SetScale(const_cast<UI&>(origin).GetScale());
    SetPos(const_cast<UI&>(origin).GetPos() + Vec2(100.f, 100.f));

    // _vecInnerUI
    for (int32 i = 0; i < origin._vecInnerUI.size(); ++i)
    {
        UI* innerUI = origin._vecInnerUI[i]->Clone();
        NULL_PTR_CHECK(innerUI);
        this->SetInnerUI(innerUI);
    }
}

UI* UI::Clone()
{
    return new UI(*this);
}

void UI::Update()
{
    // RootUI에 대해서 Hover 체크를 먼저 진행하면 안된다
    UpdateMouseInteraction();

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
    // visile == false라면 그리지 않는다.
    if (GetVisible() == false) return;

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
            int32(pos.x),               // left
            int32(pos.y),               // top
            int32(pos.x + scale.x),     // right
            int32(pos.y + scale.y)      // bottom
        );

        GDI->ReleasePen();
    }
    else 
    {
        Rectangle
        (
            GET_MEMDC,
            int32(pos.x), 
            int32(pos.y),
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
    
}

void UI::Begin()
{

}

void UI::End()
{
    _vecInnerUI.clear();
    _outerUI = nullptr;
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

void UI::UpdateMouseInteraction()
{
    bool visible = GetVisible();
    if (GetVisible() == false) return;

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
        SetMouseHoverOnThisObject(true);

        GetOuterScene()->SetCurMouseHoverObject(this);
        GetOuterScene()->SetCurMouseHoverObjectName(GetObjectName().c_str());
    }
    else
    {
        SetMouseHoverOnThisObject(false);
    }
}

void UI::EVENT_MOUSE_HOVERON_UI()
{
    
}

void UI::EVENT_MOUSE_LBTN_DOWN_UI()
{
    
}

void UI::EVENT_MOUSE_LBTN_UP_UI()
{
    
}

void UI::EVENT_MOUSE_LBTN_CLICK_UI()
{
    
}

bool UI::GetMouseHoverOnThisObject()
{
    return GetMouseHoverOnThisUI();
}

void UI::SetMouseHoverOnThisObject(bool hoverOn)
{
    SetMouseHoverOnThisUI(hoverOn);
}

void UI::SetVisible(bool visible)
{
    UI* rootUI = GetRootUI();
    rootUI->SetInnerVisible(visible);
}

void UI::SetOuterVisible(bool visible)
{
    _visible = visible;
    UI* outerUI = GetOuterUI();
    if (nullptr != outerUI)
    {
        outerUI->SetOuterVisible(false);
    }
}

void UI::SetInnerVisible(bool visible)
{
    _visible = visible;
    for (UI* innerUI : _vecInnerUI)
    {
        if (innerUI)
        {
            innerUI->SetInnerVisible(visible);
        }
    }   
}

UI* UI::GetRootUI()
{
    UI* targetUI = GetOuterUI();
    if (nullptr == targetUI) return this;
    else targetUI->GetRootUI();
}
