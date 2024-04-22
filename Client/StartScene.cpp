#include "pch.h"
#include "StartScene.h"
#include "Monster.h"
#include "Tile.h"

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
	if (KEY_PRESSED(KEYES::LBTN))
	{
		CheckTileIdx();
	}

	if (KEY_PRESSED(KEYES::DOWN))
	{
		ChnageScene_EV(SCENE_TYPE::TOOL);
	}

	Scene::Update();
}

void StartScene::Render()
{
	Scene::Render();
}

void StartScene::BeginScene()
{
	auto res = GET_RESOLUTION;

	// Create Player
	Player* player = static_cast<Player*>(CreatePlayer());
	player->SetScale(Vec2(50.f, 50.f));

	// 스폰된 오브젝트들 Init 작업
	InitObjects();

	// Call Objects Begin
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
	

	// FILE IO(1) TODO
	// LoadTile(L"Tile\\StartTile.tile");
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
