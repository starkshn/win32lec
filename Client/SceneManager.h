#pragma once
#include "Scene.h"

class SceneManager : public Manager
{
	DECLARE_SINGLE(SceneManager);

public:
	virtual void Init() override;
	virtual void Update() override;
	void Render();

private:
	void InitScene();

	inline void SetCurrentScene(SCENE_TYPE type) { _curScene = _scenes[(uint32)type]; }
	inline void SetGameFirstScene(SCENE_TYPE type) { SetCurrentScene(type); }

public:
	const SCENE_TYPE GetCurrentSceneType() 
	{ return _curScene->GetOwnSceneType(); }

	Scene* GetCurrentScene() { return _curScene; }

	Player* GetPlayer()
	{
		return _curScene->GetPlayer();
	}

private:
	void ChangeScene(SCENE_TYPE dest);
	friend class EventManager;

private:
	void CreateScene(SCENE_TYPE type, const wstring& name);

private:
	vector<Scene*> _scenes;
	Scene* _curScene		= nullptr;
};

