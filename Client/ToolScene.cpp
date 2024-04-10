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
		
		// ���콺�� render ��ǥ�� Ÿ�� render ��ǥ�� ��ġ�ϴ��� Ȯ��
		if ((renderMousePos.x <= maxX && renderMousePos.x >= tileRenderPos.x) && (renderMousePos.y <= maxY && renderMousePos.y >= tileRenderPos.y))
		{
			// ���̻� Ÿ���� ���� ��ų �� ���� ��� ó������ �ǵ���
			if (tileObj->GetTileIdx() + 1 >= MAX_TILE_COUNT)
			{
				tileObj->SetTileIdx(0);
			}
			// ���� ��ų �� �ִ� ���
			else
			{
				tileObj->SetTileIdx(tileObj->GetTileIdx() + 1);
			}
		}

		// Ŭ���� �� Ȯ���ϱ� ���� �κ�
		// ���Ŀ� Redner���� �׸� ���̴�.
		SetMouseRenderPos(renderMousePos);
		SetMouseWindowPos(windowMousePos);
	}
}

