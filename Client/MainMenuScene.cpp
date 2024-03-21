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
	auto res = GET_RESOLUTION();

	// Player
	CreatePlayer(Vec2(50.f, 50.f), Vec2(res.x / 2.f, 500.f));

	Vec2 scale			= DEFAULT_SCALE;
	float patrolDist	= DEFAULT_PATROL_DISTANCE;
	int spawnCnt = 5;

	//  Vec2{ (patrolDist + scale.x / 2) + term * i
	//float term = (res.x - (patrolDist + scale.x / 2) * 2) / (spawnCnt - 1);
	//for (int i = 0; i < spawnCnt; ++i)
	//{
	//	auto obj = SpawnDynamicObject<Monster>(OBJECT_TYPE::MONSTER, OBJECT_STATE::PATROL, Vec2((patrolDist + scale.x / 2.f) + term * i, 200.f), scale);
	//	obj->SetPatrolDistance(patrolDist);
	//	obj->SetPatrolCenterPos(obj->GetPos());
	//}

	//// spawn rotating brick
	//SpawnDynamicObject<Brick>(OBJECT_TYPE::BRICK, OBJECT_STATE::ROTATE, Vec2(res.x / 2.f, res.y / 2.f), Vec2(30.f, 30.f), 200.f);
	//SpawnDynamicObject<Brick>(OBJECT_TYPE::BRICK, OBJECT_STATE::ROTATE, Vec2(res.x / 2.f, res.y / 2.f), Vec2(30.f, 30.f), 200.f);
	//SpawnDynamicObject<Brick>(OBJECT_TYPE::BRICK, OBJECT_STATE::ROTATE, Vec2(res.x / 2.f, res.y / 2.f), Vec2(30.f, 30.f), 200.f);


	auto ob = SpawnStaticObject<Monster>(OBJECT_TYPE::MONSTER, OBJECT_STATE::DEFAULT, Vec2(100.f, 500.f), scale);
	ob->SetPos(Vec2(100.f, 100.f));

	ob = SpawnStaticObject<Monster>(OBJECT_TYPE::MONSTER, OBJECT_STATE::DEFAULT, Vec2(200.f, 500.f), scale);
	ob->SetPos(Vec2(150.f, 100.f));

	InitObjects();

	// 충돌지정
	// Player 그룹과 monster그룹간의 충돌 체크
	COLLISION->SetObjectCollisionByType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);

	COLLISION->SetObjectCollisionByType(OBJECT_TYPE::PROJECTILE, OBJECT_TYPE::MONSTER);
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
	
}

void MainMenuScene::EndScene()
{
	COLLISION->ResetObjectCollision();
}
