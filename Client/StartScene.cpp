#include "pch.h"
#include "StartScene.h"

StartScene::StartScene()
{

}

StartScene::~StartScene()
{

}

void StartScene::InitScene()
{
	auto res = GET_RESOLUTION();

	CreatePlayer(DEFAULT_SCALE, Vec2(res.x / 2.f, 500.f));

	auto projLine = SpawnDynamicObject<ProjectileLine>(OBJECT_TYPE::PROJECTILE_LINE, OBJECT_STATE::DEFAULT, Vec2(GetPlayer()->GetPos().x + 50.f, GetPlayer()->GetPos().y), Vec2(100.f, 5.f), 0.f);
	
	InitObjects();
}

void StartScene::Update()
{
	Scene::Update();
}

void StartScene::Render()
{
	Scene::Render();
}

void StartScene::BeginScene()
{
	for (int i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (auto obj : _sceneObjects[i])
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
		for (auto obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->End();
			}
		}
	}
}
