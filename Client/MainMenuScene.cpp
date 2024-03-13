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
	AddObject<Player>(OBJECT_TYPE::PLAYER, Vec2{ 100.f, 100.f }, Vec2{ 300.f, 300.f} );

	// AddObject<Brick>(OBJECT_TYPE::BRICK, Vec2{ 100.f, 100.f }, Vec2{ 100.f, 100.f });

	auto res = GET_RESOLUTION();
	Vec2 scale = Vec2(50.f, 50.f);
	float patrolDist = 100.f;
	int spawnCnt = 3;

	float term = (res.x - (patrolDist + scale.x / 2) * 2) / (spawnCnt - 1);
	for (int i = 0; i < spawnCnt; ++i)
	{
		AddObject<Monster>(OBJECT_TYPE::MONSTER, scale, Vec2{ (patrolDist + scale.x / 2) + term * i , 200.f });
		auto obj = GetSceneObject(OBJECT_TYPE::MONSTER);

		// init
		obj->SetSpeed(50.f);
		obj->SetPatrolCenterPos(obj->GetPos());
		obj->SetPatrolDistance(patrolDist);
		obj->SetDir(Vec2(1, 0));
	}
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
