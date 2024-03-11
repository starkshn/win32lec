#include "pch.h"
#include "MainMenuScene.h"
#include "Object.h"

MainMenuScene::MainMenuScene()
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::InitScene()
{
	AddObject<Object>(OBJECT_TYPE::RECTANGLE, Vec2{ 100.f, 100.f }, Vec2{ 300.f, 300.f} );
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
