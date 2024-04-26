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
	// RenderObject();
	RenderObjectMy();
}

void Scene::CreateTile(uint32 tileXCount, uint32 tileYCount)
{
	DeleteAllObjectsByType(OBJECT_TYPE::DEFAULT_TILE);

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

void Scene::RenderObject()
{
	for (uint32 i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		if (OBJECT_TYPE::DEFAULT_TILE == OBJECT_TYPE(i))
		{
			RenderTile();
			continue;
		}

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
				//if (OBJECT_TYPE::DEFAULT_TILE == OBJECT_TYPE(i))
				//{
				//	if (TileRenderOptimization(*(*iter)))
				//	{
				//		(*iter)->Render();
				//	}
				//}
				//else
				//{
				//	(*iter)->Render();
				//}
				//++iter;

				(*iter)->Render();
				++iter;
			}
		}
	}
}

void Scene::RenderObjectMy()
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
				if (OBJECT_TYPE::DEFAULT_TILE == OBJECT_TYPE(i))
				{
					if (TileRenderOptimization(*(*iter)))
					{
						(*iter)->Render();
					}
				}
				else
				{
					(*iter)->Render();
				}
				++iter;
			}
		}
	}
}

void Scene::RenderTile()
{
	const vector<Object*>& vecTiles = GetObjectsByType(OBJECT_TYPE::DEFAULT_TILE);
	if (vecTiles.size() == 0) return;

	Vec2 res = GET_RESOLUTION;

	Vec2 cameraLookAtPos = CAMERA->GetCameraCurrentLookAtPos();
	Vec2 leftTopPos = cameraLookAtPos - res / 2.f; // 좌상단
	
	int32 tileSize = TILE_SIZE;
	
	// LT 행열 구하기
	int32 tileLeftTopCol = leftTopPos.x / tileSize;
	int32 tileLeftTopRow = leftTopPos.y / tileSize;

	// 타일 개수 가져오기
	Vec2 tileCounts = GetCurrentTileXYCount();
	int32 tileXCount = int32(tileCounts.x);
	int32 tileYCount = int32(tileCounts.y);

	// LT 타일의 인덱스
	int32 tileLeftTopIdx = tileXCount * tileLeftTopRow + tileLeftTopCol;
	
	// 화면에 보여줄 타일 개수
	int32 renderTileXCount = int32(res.x) / tileSize + 2;
	int32 renderTileYCount = int32(res.y) / tileSize + 1;

	// 렌더할 타일 계산
	for (int32 curRow = tileLeftTopRow; curRow < tileLeftTopRow + renderTileYCount; ++curRow)
	{
		for (int32 curCol = tileLeftTopCol; curCol < tileLeftTopCol + renderTileXCount; ++curCol)
		{
			if (curCol < 0 || tileXCount <= curCol || curRow < 0 || tileYCount <= curRow)
			{
				continue;
			}
			
			// 인덱스를 구하고 해당하는 타일을 그린다.
			int32 curIdx = tileXCount * curRow + curCol;
			vecTiles[curIdx]->Render();
		}
	}
}

bool Scene::TileRenderOptimization(Object& tile)
{
	Vec2 res = GET_RESOLUTION;
	Vec2 renderPos = tile.GetPos();
	Vec2 scale = tile.GetScale();
	Vec2 cameraPos = CAMERA->GetCameraCurrentLookAtPos();
	float tileSize = static_cast<float>(TILE_SIZE);
	
	float minX = renderPos.x;
	float maxX = renderPos.x + scale.x;
	float minY = renderPos.y;
	float maxY = renderPos.y + scale.y;
	
	// 렌더링 잘되는지 확인할려고 tileSize -+ 해줌 (빼면 껌뻑껌뻑 거리는거 사라짐)
	float cameraMinX = (cameraPos.x - res.x / 2.f) + tileSize;
	float cameraMaxX = (cameraPos.x + res.x / 2.f) - tileSize;
	float cameraMinY = (cameraPos.y - res.y / 2.f) + tileSize;
	float cameraMaxY = (cameraPos.y + res.y / 2.f) - tileSize;

	if (maxX < cameraMinX || minX > cameraMaxX || minY > cameraMaxY || maxY < cameraMinY) return false;
	return true;
}

bool Scene::ObjectRenderOptimization(Object& object)
{
	
	return false;
}

void Scene::UpdateTextOfGameInfo()
{
	_vecGameInfoTexts[uint32(GAME_INFO::GAMEINFO_FPS)] = L"FPS : " + to_wstring(FPS);
	_vecGameInfoTexts[uint32(GAME_INFO::GAMEINFO_DT)] = L"DeltaTime : " + to_wstring(DT_F);

	uint32 objCount = GetSceneAllObjectCount();
	_vecGameInfoTexts[uint32(GAME_INFO::GAMEINFO_OBJECT_COUNT)] = L"Objet Count : " + to_wstring(objCount);

	Object* curObject = GetCurMouseHoverObject();
	wstring curObjectName = L"None";
	if (nullptr != curObject)
	{
		if (curObject->GetMouseHoverOnThisObject())
		{
			curObjectName = curObject->GetObjectName();
		}
	}

	_vecGameInfoTexts[uint32(GAME_INFO::GAMEINFO_CUR_OBJECT)] = L"Objet Name : " + curObjectName;
}

void Scene::RenderTextOfGameInfo()
{
	for (uint32 i = 0; i < uint32(GAME_INFO::END); ++i)
	{
		if (_vecGameInfoTexts.size() != 0)
		{
			if (_vecGameInfoTexts[i] != L"")
			{
				TextOut(GET_MEMDC, 10, int32(50.f + i * 20.f), _vecGameInfoTexts[i].c_str(), int32(_vecGameInfoTexts[i].length()));
			}
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

void Scene::ResetSceneInfo()
{
	_vecGameInfoTexts.clear();
	_tileXCount = 0;
	_tileYCount = 0;
	_curHoverOnObject = nullptr;
	_curHoverOnObjectName = L"None";
	_curMouseHoverOnObject = nullptr;
	_curMouseLBTNDownObject = nullptr;
}

void Scene::LoadTile(const wstring& relativePath)
{
	
}


