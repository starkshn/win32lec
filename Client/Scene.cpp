#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Tile.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (uint32 i = 0; i < static_cast<uint32>(OBJECT_TYPE::END); ++i)
	{
		for (uint32 j = 0; j < _sceneObjects[i].size(); ++j)
		{
			if (nullptr != _sceneObjects[i][j])
			{
				delete _sceneObjects[i][j];
			}
		}
	}
}

void Scene::Update()
{
	for (uint32 i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
		{
			if (obj)
			{
				if (obj->GetThisObjectWillDelete() == false)
				{
					obj->Update();
				}
			}
		}
	}
}

void Scene::FinalUpdate()
{
	for (uint32 i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->FinalUpdate();
			}
		}
	}
}

void Scene::Render()
{
	for (uint32 i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		vector<Object*>::iterator iter = _sceneObjects[i].begin();

		for (; iter < _sceneObjects[i].end();)
		{
			// 삭제될 경우 렌더하지 않고 없애준다.
			// 벡터에서 없앤다.
			if ((*iter)->GetThisObjectWillDelete())
			{
				// [] [] [e] []
				// [] [] [] [e] 
				iter = _sceneObjects[i].erase(iter);
			}
			// 삭제되지 않는경우 iter를 증가시킨다.
			else
			{
				(*iter)->Render();
				++iter;
			}
		}
	}
}

void Scene::CreateTile(uint32 tileXCount, uint32 tileYCount)
{
	Texture* tileTex = static_cast<Texture*>(RESOURCE->LoadTexture(L"Tile", L"texture\\tile.bmp"));

	// Set Tile Pos
	for (uint32 i = 0; i < tileYCount; ++i)
	{
		for (uint32 j = 0; j < tileXCount; ++j)
		{
			Tile* tile = static_cast<Tile*>(CreateAndAppendToScene<Tile>(OBJECT_TYPE::DEFAULT_TILE));

			tile->SetScale(Vec2(TILE_SIZE, TILE_SIZE));

			Vec2 scale = tile->GetScale();
			tile->SetOffSet(Vec2(scale.x / 2.f, scale.y / 2.f));

			int x = j * TILE_SIZE;
			int y = i * TILE_SIZE;
			tile->SetPos(Vec2(float(x), float(y)));
			tile->SetTexture(tileTex);
			tile->SetTileType(TILE_TYPE::EMPTY);
		}
	}

	SetCurrentTileXYCount(Vec2(float(tileXCount), float(tileYCount)));

	// Init Tile Tex
	InitObjects();
}

void Scene::CheckTileIdx()
{
	Vec2 renderMousePos = KEY->GetMousePos();
	Vec2 windowMousePos = GET_WINDOW_MOUSE_POS(renderMousePos);

	Vec2 tileCount = GetCurrentTileXYCount();
	int32 tileXCount = (int32)tileCount.x;
	int32 tileYCount = (int32)tileCount.y;

	int32 tileColIdx = int32(windowMousePos.x / TILE_SIZE);
	int32 tileRowIdx = int32(windowMousePos.y / TILE_SIZE);

	// Check Index Out Of Range
	if ((tileColIdx >= tileXCount) || (tileRowIdx >= tileYCount) || tileColIdx < 0 || tileRowIdx < 0)
	{
		return;
	}

	// Get Tile Object
	uint32 tileObjectIdx = (tileRowIdx * tileXCount) + tileColIdx;
	Tile* tileObj = dynamic_cast<Tile*>(GetObjectByTypeAndIndex(OBJECT_TYPE::DEFAULT_TILE, tileObjectIdx));
	NULL_PTR_CHECK(tileObj);
	int32 tileID = tileObj->GetTileID();
		
	Vec2 tileRenderPos = tileObj->GetRenderPos();
	Vec2 tileWindowPos = CAMERA->GetWindowActualPosFromRenderPos(tileRenderPos);
	
	int32 tileMaxXRange = int32(tileRenderPos.x + tileObj->GetScale().x);
	int32 tileMaxYRange = int32(tileRenderPos.y + tileObj->GetScale().y);
		
	// 마우스의 render 좌표와 타일 render 좌표가 일치하는지 확인
	if (
		(renderMousePos.x <= tileMaxXRange && renderMousePos.x >= tileRenderPos.x) && 
		(renderMousePos.y <= tileMaxYRange && renderMousePos.y >= tileRenderPos.y)
		)
	{
		TILE_TYPE type = tileObj->GetTileType();
		if (type == TILE_TYPE::EMPTY)
		{
			Vec2 tilePos = tileObj->GetPos();
			Vec2 destPos = Vec2(tilePos.x + TILE_SIZE / 2, tilePos.y + TILE_SIZE / 2);

			GET_PLAYER->PushDestTileID(tileID);
		}
	}
}


void Scene::InitObjects()
{
	for (uint32 i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->Init();
			}
		}
	}
}

void Scene::InitObjectCollision(OBJECT_TYPE ltype, OBJECT_TYPE rtype)
{
	COLLISION->SetObjectCollisionByType(ltype, rtype);
}

void Scene::ObjectBegin()
{
	for (int i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->Begin();
			}
		}
	}
}

void Scene::DeleteAllObjectsByType(OBJECT_TYPE type)
{
	DeleteObjectsSafe<Object*>(_sceneObjects[(uint32)type]);
}

void Scene::DeleteAllObjects()
{
	for (uint32 i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		DeleteAllObjectsByType((OBJECT_TYPE)i);
	}
}


