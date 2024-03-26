#pragma once

#include "Object.h"
#include "Player.h"
#include "Rect.h"
#include "Brick.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void InitScene() abstract;
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void BeginScene() abstract;
	virtual void EndScene() abstract;

public:
	void SetName(const wstring& name) 
	{
		_sceneName = name; 
	}

	const wstring& GetName()
	{ 
		return _sceneName;
	}

	void SetSceneType(const SCENE_TYPE type)
	{ 
		_sceneType = type;
	}

	const SCENE_TYPE GetOwnSceneType() 
	{ 
		return _sceneType;
	}

public:
	// col
	const vector<Object*>& GetObjectsByType(OBJECT_TYPE type)
	{
		return _sceneObjects[(uint32)type];
	}

	void AddObject(Object* obj, OBJECT_TYPE type)
	{
		_sceneObjects[(uint32)type].push_back(obj);
		_sceneObjects[(uint32)type].back()->SetOuterScene(this);
		_sceneObjects[(uint32)type].back()->SetOuterSceneType(this->GetOwnSceneType());
	}

	void CreatePlayer(Player* player)
	{
		AddObject(player, OBJECT_TYPE::PLAYER);
	}

public:
	void InitObjects();
	
	const Player* GetPlayer() 
	{ 
		return static_cast<Player*>(_sceneObjects[(uint32)OBJECT_TYPE::PLAYER].back());
	}

protected:
	void RemoveObject();
	void FindObject();

protected:
	vector<Object*>		_sceneObjects[MAX_LENGH];
	wstring				_sceneName = L"";
	SCENE_TYPE			_sceneType = SCENE_TYPE::END;
};	

