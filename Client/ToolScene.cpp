#include "pch.h"
#include "ToolScene.h"
#include "Tile.h"
#include "Texture.h"
#include "TimeManager.h"

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
	// Set Camera
	Vec2 res = GET_RESOLUTION;
	CAMERA->SetCameraCurrentLookAtPos(Vec2(res.x / 2.f, res.y / 2.f));
}

void ToolScene::EndScene()
{
	
}


void ToolScene::ChangeTileIndex()
{
	if (KEY_PRESSED(KEYES::LBTN))
	{
		// render pos -> window pos
		Vec2 renderMousePos = KEY->GetMousePos();
		Vec2 windowMousePos = GET_WINDOW_MOUSE_POS(renderMousePos);
		
		Vec2 tileCount		= GetCurrentTileXYCount();
		uint32 tileXCount	= (uint32)tileCount.x;
		uint32 tileYCount	= (uint32)tileCount.y;

		uint32 tileColIdx = uint32(windowMousePos.x / TILE_SIZE);
		uint32 tileRowIdx = uint32(windowMousePos.y / TILE_SIZE);

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
		uint32 maxX = tileRenderPos.x + tileObj->GetScale().x;
		uint32 maxY = tileRenderPos.y + tileObj->GetScale().y;
		
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

		// 클릭한 곳 확인하기 위한 부분
		// 추후에 Redner에서 그릴 것이다.
		SetMouseRenderPos(renderMousePos);
		SetMouseWindowPos(windowMousePos);
	}
}

