#include "pch.h"
#include "ToolScene.h"
#include "Tile.h"
#include "Texture.h"
#include "TimeManager.h"
#include "PanelUI.h"
#include "ButtonUI.h"


ToolScene::ToolScene()
{

}

ToolScene::~ToolScene()
{

}

void ToolScene::InitScene()
{
	
}

void ToolScene::Update()
{
	Scene::Update();

	ChangeTileIndex();
}

void ToolScene::Render()
{
	Scene::Render();
}

void ToolScene::BeginScene()
{
	Player* player = static_cast<Player*>(CreatePlayer());
	player->SetScale(Vec2(50.f, 50.f));
	player->SetPos(Vec2(GET_RESOLUTION.x / 2.f, GET_RESOLUTION.y / 2.f));

	// Set Camera
	Vec2 res = GET_RESOLUTION;
	CAMERA->SetCameraCurrentLookAtPos(Vec2(res.x / 2.f, res.y / 2.f));
	
	// 패널 UI
	UI* outer_PanelUI = static_cast<UI*>(CreateAndAppendToScene<PanelUI>(OBJECT_TYPE::UI));
	outer_PanelUI->SetObjectName(L"PanelUI");
	outer_PanelUI->SetScale(Vec2(500.f, 300.f));
	outer_PanelUI->SetPos(Vec2(300.f, 300.f));
	outer_PanelUI->SetUIOffSet(Vec2(0.f, 0.f));

	// 버튼 UI
	UI* inner_ButtonUI = static_cast<UI*>(CreateAndAppendToScene<ButtonUI>(OBJECT_TYPE::UI));
	inner_ButtonUI->SetScale(Vec2(100.f, 100.f));
	inner_ButtonUI->SetUIOffSet(Vec2(0.f, 0.f));
	inner_ButtonUI->SetObjectName(L"ButtonUI");
	
	outer_PanelUI->SetInnerUI(inner_ButtonUI);

	UI* ClonePanel = outer_PanelUI->Clone();
	ClonePanel->SetPos(outer_PanelUI->GetPos() + Vec2(200.f, 0.f));
}

void ToolScene::EndScene()
{
	
}

void ToolScene::ChangeTileIndex()
{
	if (KEY_PRESSED(KEYES::LBTN))
	{
		// render pos -> window pos
		/*Vec2 renderMousePos = KEY->GetMousePos();
		Vec2 windowMousePos = GET_WINDOW_MOUSE_POS(renderMousePos);*/

		// 현재 윈도우 렌더링 마우스 좌표
		Vec2 renderMousePos = RENDER_MOUSE_POS;

		// 현재 윈도우 실제 마우스 좌표 (절대 좌표)
		Vec2 windowMousePos = WINDOW_MOUSE_POS;
		
		// 현재 씬 타일 X Y 개수 반환
		Vec2 tileXYCount	= GetCurrentTileXYCount();
		int32 tileXCount	= (int32)tileXYCount.x;
		int32 tileYCount	= (int32)tileXYCount.y;

		int32 tileColIdx = int32(windowMousePos.x / TILE_SIZE);
		int32 tileRowIdx = int32(windowMousePos.y / TILE_SIZE);

		// index range check
		if ((tileColIdx >= tileXCount) || (tileRowIdx >= tileYCount)) return;

		uint32 tileObjectIdx = (tileRowIdx * tileXCount) + tileColIdx;
		Tile* tileObj = static_cast<Tile*>(GetObjectByTypeAndIndex(OBJECT_TYPE::DEFAULT_TILE, tileObjectIdx));
		if (nullptr == tileObj)
		{
			assert(0);
			return;
		}

		Vec2 tileRenderPos = tileObj->GetRenderPos();
		int32 maxX = int32(tileRenderPos.x + tileObj->GetScale().x);
		int32 maxY = int32(tileRenderPos.y + tileObj->GetScale().y);
		
		// 마우스의 render 좌표와 타일 render 좌표가 일치하는지 확인
		if ((renderMousePos.x <= maxX && renderMousePos.x >= tileRenderPos.x) && (renderMousePos.y <= maxY && renderMousePos.y >= tileRenderPos.y))
		{
			// 더이상 타일을 증가 시킬 수 없는 경우 처음으로 되돌림
			if (tileObj->GetTileIdx() + 1 >= MAX_TILE_COUNT)
			{
				tileObj->SetTileIdx(0);
			}
			// 증가 시킬 수 있는 경우
			else
			{
				tileObj->SetTileIdx(tileObj->GetTileIdx() + 1);
			}
		}
	}
}

