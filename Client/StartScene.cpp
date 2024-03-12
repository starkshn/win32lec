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
	AddObject<Object>(OBJECT_TYPE::RECTANGLE, Vec2{ 200.f, 200.f }, Vec2{ 300.f, 300.f });
}

void StartScene::Update()
{
	Scene::Update();
}

void StartScene::Render()
{
	Scene::Render();
}

void StartScene::EnterScene()
{
}

void StartScene::ExitScene()
{
}
