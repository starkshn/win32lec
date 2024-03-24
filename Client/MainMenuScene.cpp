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
	auto res = GET_RESOLUTION;

	// Player
	Player* player = new Player();
	CreatePlayer(player);

	Vec2 scale			= DEFAULT_SCALE;
	float patrolDist	= DEFAULT_PATROL_DISTANCE;
	int spawnCnt		= 5;

	Object* monster = static_cast<Object*>(new Monster());
	AddObject(monster, OBJECT_TYPE::MONSTER);

	/*monster = static_cast<Object*>(new Monster());
	AddObject(monster, OBJECT_TYPE::MONSTER);

	monster = static_cast<Object*>(new Monster());
	AddObject(monster, OBJECT_TYPE::MONSTER);*/
			
	

	// 충돌지정
	// Player 그룹과 monster그룹간의 충돌 체크
	// COLLISION->SetObjectCollisionByType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);

	// COLLISION->SetObjectCollisionByType(OBJECT_TYPE::PROJ_PLAYER, OBJECT_TYPE::MONSTER);

	InitObjects();
}

void MainMenuScene::Update()
{
	Scene::Update();
}

void MainMenuScene::Render()
{
	Scene::Render();
}

void MainMenuScene::BeginScene()
{
	COLLISION->SetObjectCollisionByType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);

	COLLISION->SetObjectCollisionByType(OBJECT_TYPE::PROJ_PLAYER, OBJECT_TYPE::MONSTER);
}

void MainMenuScene::EndScene()
{
	COLLISION->ResetObjectCollision();
}
