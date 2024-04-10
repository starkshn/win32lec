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
		}
	}

	// Init Tile Tex
	InitObjects();
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


