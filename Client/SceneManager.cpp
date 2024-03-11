#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "MainMenuScene.h"
#include "StartScene.h"


SceneManager::SceneManager()
{
	_scenes.resize(MAX_LENGH);
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::Init()
{
	// make scenes.
	InitScene();

	// set first scene.
	SetGameFirstScene(SCENE_TYPE::MAIN_MENU);

	// TODO
	// enter scene
	_curScene->EnterScene();
}

void SceneManager::Update()
{
	_curScene->Update();
}

void SceneManager::Render()
{
	_curScene->Render();
}

void SceneManager::InitScene()
{
	// Add scenes...
	CreateScene<MainMenuScene>(SCENE_TYPE::MAIN_MENU, L"MainMenu");
	CreateScene<StartScene>(SCENE_TYPE::START, L"StartScene");

	// init -> create all objects...
	for (const auto& scene : _scenes)
	{
		if (scene) scene->InitScene();
	}
}
