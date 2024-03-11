#pragma once

#include "Scene.h"
#include "MainMenuScene.h"
#include "StartScene.h"

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

private:
	template <typename T>
	void CreateScene(SCENE_TYPE type, const wstring& name)
	{
		auto scene = make_shared<T>();
		_scenes[uint32(type)] = (scene);
		_scenes[(uint32)type].get()->SetName(name);
		_scenes[(uint32)type].get()->SetSceneType(type);
	}

private:
	vector<shared_ptr<Scene>> _scenes;
	shared_ptr<Scene> _curScene;
};

