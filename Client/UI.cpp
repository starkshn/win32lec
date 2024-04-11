#include "pch.h"
#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
    DeleteObjectsSafe(_vecInnerUI);
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
    // TODO MY Job
    Object::FinalUpdate();
    
    // outer UI없는 경우 현재 offset이 최종 위치가 된다.
    SetUIFinalPos(GetUIOffSet());

    if (UI* outerUI = GetOuterUI())
    {
        Vec2 outerUIFinalPos = outerUI->GetUIFinalPos();
        SetUIFinalPos(GetUIFinalPos() + outerUIFinalPos);
    }

    // Final Update InnerUI
    FinalUpdateInnerUI();
}

void UI::Render()
{
    // TODO My job
    Vec2 pos    = GetUIFinalPos();
    Vec2 scale  = GetScale();
    
    Rectangle
    (
        GET_MEMDC,
        int32(pos.x), int32(pos.y),
        int32(pos.x + scale.x),
        int32(pos.y + scale.y)
    );
    
    // Render Inner UI
    RenderInnerUI();
}

void UI::Init()
{
    // temp
    // 우측상단 위치
    Vec2 res = GET_RESOLUTION;
    SetScale(Vec2(100.f, 30.f));
    SetPos(Vec2(res.x - GetScale().x, 0));
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
