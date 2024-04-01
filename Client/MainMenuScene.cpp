#include "pch.h"
#include "MainMenuScene.h"
#include "Object.h"
#include "Player.h"
#include "Rect.h"
#include "Brick.h"
#include "Monster.h"
#include "Texture.h"

MainMenuScene::MainMenuScene()
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::InitScene()
{
	
}

void MainMenuScene::Update()
{
	Scene::Update();

	if (KEY_PRESSED(KEYES::DOWN))
	{
		ChnageScene_EV(SCENE_TYPE::START);
	}
}

void MainMenuScene::Render()
{
	Scene::Render();
}

void MainMenuScene::BeginScene()
{
	auto res = GET_RESOLUTION;

	// Player
	Player* oriPlayer = static_cast<Player*>(CreatePlayer());

	Vec2 scale = DEFAULT_SCALE;
	float patrolDist = DEFAULT_PATROL_DISTANCE;
	int spawnCnt = 5;

	CreateAndAppendToScene<Monster>(OBJECT_TYPE::MONSTER);

	// 스폰된 오브젝트들 Init 작업
	InitObjects();

	// 복사생성자
	/*Object* newPlayer2 = oriPlayer->Clone();
	newPlayer2->SetPos(Vec2(100.f, 500.f));
	AddObjectToCurrentScene(newPlayer2, OBJECT_TYPE::PLAYER);*/

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

void MainMenuScene::EndScene()
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
