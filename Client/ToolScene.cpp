#include "pch.h"
#include "ToolScene.h"
#include "Tile.h"
#include "Texture.h"
#include "TimeManager.h"
#include "UI.h"

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
	
	UI* outerUI = static_cast<UI*>(CreateAndAppendToScene<UI>(OBJECT_TYPE::UI));
	outerUI->SetScale(Vec2(200.f, 100.f));
	outerUI->SetPos(Vec2(res.x - outerUI->GetScale().x, 0.f));
	outerUI->SetUIOffSet(Vec2(0.f, 0.f));

	UI* innerUI = static_cast<UI*>(CreateAndAppendToScene<UI>(OBJECT_TYPE::UI));
	innerUI->SetScale(Vec2(50.f, 50.f));
	innerUI->SetUIOffSet(Vec2(20.f, 20.f));

	outerUI->SetInnerUI(innerUI);
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
		int32 tileXCount	= (int32)tileCount.x;
		int32 tileYCount	= (int32)tileCount.y;

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
	}
}

