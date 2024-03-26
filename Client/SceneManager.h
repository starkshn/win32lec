#pragma once

#include "Scene.h"
#include "MainMenuScene.h"
#include "StartScene.h"
#include "Player.h"

class SceneManager : public Manager
{
	DECLARE_SINGLE(SceneManager);

public:
	virtual void Init() override;
	virtual void Update() override;
	void Render();

private:
	void InitScene();

	inline void SetCurrentScene(SCENE_TYPE type)
	{
		_curScene = _scenes[(uint32)type];
	}

	inline void SetGameFirstScene(SCENE_TYPE type)
	{
		SetCurrentScene(type);
	}

public:
	const SCENE_TYPE GetCurrentSceneType()
	{
		return _curScene->GetOwnSceneType();
	}

	Scene* GetCurrentScene()
	{
		return _curScene;
	}

	const Player* GetPlayer()
	{
		return GetCurrentScene()->GetPlayer();
	}

	// temp
	void ChangeScene(SCENE_TYPE type)
	{
		/*auto to = _scenes[(uint32)type];
		to->EndScene();
		_curScene.swap(to);
		_curScene->BeginScene();*/
	}

private:
	void CreateScene(SCENE_TYPE type, const wstring& name)
	{
		switch (type)
		{
		case SCENE_TYPE::MAIN_MENU:
		{
			Scene* scene = new MainMenuScene();
			_scenes[uint32(type)] = (scene);
			_scenes[(uint32)type]->SetName(name);
			_scenes[(uint32)type]->SetSceneType(type);
		}
			break;
		case SCENE_TYPE::START:
		{
			Scene* scene = new StartScene();
			_scenes[uint32(type)] = (scene);
			_scenes[(uint32)type]->SetName(name);
			_scenes[(uint32)type]->SetSceneType(type);
		}
			break;
		case SCENE_TYPE::STAGE_01:
		{

		}
			break;
		case SCENE_TYPE::STAGE_02:
			break;
		case SCENE_TYPE::TOOL:
			break;
		case SCENE_TYPE::END:
			break;
		default:
			break;
		}
	}

private:
	vector<Scene*> _scenes;
	Scene* _curScene		= nullptr;
};

