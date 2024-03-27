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
	// 타입에 따라 오브젝트'들'을 반환하는 함수
	const vector<Object*>& GetObjectsByType(OBJECT_TYPE type)
	{
		return _sceneObjects[(uint32)type];
	}

	// 오브젝트를 씬에 추가해주는 함수
	void AddObjectToCurrentScene(Object* obj, OBJECT_TYPE type)
	{
		_sceneObjects[(uint32)type].push_back(obj);
		obj->SetOuterScene(this);
		obj->SetOuterSceneType(this->GetOwnSceneType());
	}

	// 타입에 따라 오브젝트를 생성하고 씬에 추가해주는 함수
	template<typename T>
	Object* CreateAndAppendToScene(OBJECT_TYPE type)
	{
		T* obj = new T;

		_sceneObjects[(uint32)type].push_back(obj);
		obj->SetOuterScene(this);
		obj->SetOuterSceneType(this->GetOwnSceneType());

		return obj;
	}

	// 플레이어 생성과 씬에 추가를 해주는 함수
	Object* CreatePlayer()
	{
		return CreateAndAppendToScene<Player>(OBJECT_TYPE::PLAYER);
	}

	// 현재씬의 플레이어 반환해주는 함수
	Player* GetPlayer()
	{
		return static_cast<Player*>(_sceneObjects[(uint32)OBJECT_TYPE::PLAYER].back());
	}

protected:
	// Scene Begin호출후 오브젝트 초기값 셋팅들
	void InitObjects();

protected:
	// Scene변경될 때 호출 될 함수들
	virtual void DeleteAllObjectsByType(OBJECT_TYPE type);
	void DeleteAllObjects();

protected:
	vector<Object*>		_sceneObjects[MAX_LENGH];
	wstring				_sceneName = L"";
	SCENE_TYPE			_sceneType = SCENE_TYPE::END;
};	

