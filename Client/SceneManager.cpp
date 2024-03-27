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
	for_each
	(
		_scenes.begin(), _scenes.end(),
		[&](Scene* scene)
		{
			if (scene != nullptr)
			{
				delete scene;
				scene = nullptr;
			}
		}
	);
}

void SceneManager::Init()
{
	// make scenes.
	InitScene();

	// set first scene.
	SetGameFirstScene(SCENE_TYPE::MAIN_MENU);

	// TODO
	// enter scene
	_curScene->BeginScene();
}

void SceneManager::Update()
{
	_curScene->Update();

	_curScene->FinalUpdate();
}

void SceneManager::Render()
{
	_curScene->Render();
}

void SceneManager::InitScene()
{
	// Add scenes.
	CreateScene(SCENE_TYPE::MAIN_MENU, L"MainMenu");
	CreateScene(SCENE_TYPE::START, L"StartScene");

	// init -> create all objects.
	for (const auto& scene : _scenes)
	{
		if (scene) scene->InitScene();
	}
}

// EVENT�� ���� ȣ��ȴ�.
void SceneManager::ChangeScene(SCENE_TYPE dest)
{
	// ������ �߻��� ������ �ٺ��ϴ�. -> �̺�Ʈ ����ؾ��Ѵ�.
	// _curScene = _scenes[(UINT)dest];
	
	_curScene->EndScene();

	_curScene = _scenes[(UINT)dest];

	_curScene->BeginScene();
}
