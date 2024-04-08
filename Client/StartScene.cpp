#include "pch.h"
#include "StartScene.h"
#include "Monster.h"

StartScene::StartScene()
{

}

StartScene::~StartScene()
{

}

void StartScene::InitScene()
{
	
}

void StartScene::Update()
{
	Scene::Update();

	/*if (KEY_PRESSED(KEYES::UP))
	{
		ChnageScene_EV(SCENE_TYPE::MAIN_MENU);
	}*/
}

void StartScene::Render()
{
	Scene::Render();
}

void StartScene::BeginScene()
{
	auto res = GET_RESOLUTION;

	// Player
	CreatePlayer();

	Vec2 scale = DEFAULT_SCALE;
	float patrolDist = DEFAULT_PATROL_DISTANCE;
	int spawnCnt = 5;

	Object* obj = CreateAndAppendToScene<Monster>(OBJECT_TYPE::MONSTER);
	obj->SetPos(Vec2(100.f, 100.f));

	// 스폰된 오브젝트들 Init 작업
	InitObjects();

	COLLISION->SetObjectCollisionByType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);

	COLLISION->SetObjectCollisionByType(OBJECT_TYPE::PROJ_PLAYER, OBJECT_TYPE::MONSTER);

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

void StartScene::EndScene()
{
	for (int i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->End();
			}
		}
	}

	COLLISION->ResetObjectCollision();

	DeleteAllObjects();
}
