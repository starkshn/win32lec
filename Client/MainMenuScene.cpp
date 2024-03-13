#include "pch.h"
#include "MainMenuScene.h"
#include "Object.h"
#include "Player.h"
#include "Rect.h"
#include "Brick.h"
#include "Monster.h"

MainMenuScene::MainMenuScene()
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::InitScene()
{
	auto res = GET_RESOLUTION();

	CreatePlayer(Vec2(res.x / 2, 500), Vec2(70.f, 70.f));

	Vec2 scale			= DEFAULT_SCALE;
	float patrolDist	= DEFAULT_PATROL_DISTANCE;
	int spawnCnt = 5;

	//  Vec2{ (patrolDist + scale.x / 2) + term * i
	float term = (res.x - (patrolDist + scale.x / 2) * 2) / (spawnCnt - 1);
	for (int i = 0; i < spawnCnt; ++i)
	{
		SpawnDynamicObject<Monster>(OBJECT_TYPE::MONSTER, OBJECT_STATE::PATROL, Vec2((patrolDist + scale.x / 2) + term * i, 200.f), scale);
	}

	// spawn rotating brick
	SpawnDynamicObject<Brick>(OBJECT_TYPE::BRICK, OBJECT_STATE::ROTATE, Vec2(res.x / 2, res.y / 2), Vec2(30.f, 30.f), 200.f);

	SpawnDynamicObject<Brick>(OBJECT_TYPE::BRICK, OBJECT_STATE::ROTATE, Vec2(res.x / 2, res.y / 2), Vec2(30.f, 30.f), 200.f);

	SpawnDynamicObject<Brick>(OBJECT_TYPE::BRICK, OBJECT_STATE::ROTATE, Vec2(res.x / 2, res.y / 2), Vec2(30.f, 30.f), 200.f);
}

void MainMenuScene::Update()
{
	Scene::Update();
}

void MainMenuScene::Render()
{
	Scene::Render();
}

void MainMenuScene::EnterScene()
{

}

void MainMenuScene::ExitScene()
{
}
