#include "pch.h"
#include "PanelUI.h"
#include "UI.h"

PanelUI::PanelUI()
{

}

PanelUI::PanelUI(const PanelUI& origin)
	: 
	UI(origin)
{
	Scene* curScene = SCENE->GetCurrentScene();
	curScene->PushBackObjectByType(this, OBJECT_TYPE::UI);
}

PanelUI::~PanelUI()
{

}

PanelUI* PanelUI::Clone()
{
	return new PanelUI(*this);
}

void PanelUI::Update()
{
	if (GetVisible() == false) return;
	UI::Update();
}

void PanelUI::FinalUpdate()
{
	if (GetVisible() == false) return;
	UI::FinalUpdate();
}

void PanelUI::Render()
{
	if (GetVisible() == false) return;
	UI::Render();
}

void PanelUI::Init()
{
	UI::Init();
}

void PanelUI::Begin()
{
	UI::Begin();
}

void PanelUI::End()
{
	UI::End();
}

void PanelUI::EVENT_MOUSE_HOVERON_UI()
{
	if (GetLBTNDownOnThisUI())
	{
		Vec2 diffDistance = RENDER_MOUSE_POS - _dragStartPos;
		
		Vec2 curPos = GetPos();
		curPos += diffDistance;
		SetPos(curPos);

		_dragStartPos = RENDER_MOUSE_POS;
	}
}

void PanelUI::EVENT_MOUSE_LBTN_DOWN_UI()
{
	_dragStartPos = RENDER_MOUSE_POS;
}

void PanelUI::EVENT_MOUSE_LBTN_UP_UI()
{

}

void PanelUI::EVENT_MOUSE_LBTN_CLICK_UI()
{

}
