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
	// Ÿ�Կ� ���� ������Ʈ'��'�� ��ȯ�ϴ� �Լ�
	const vector<Object*>& GetObjectsByType(OBJECT_TYPE type)
	{
		return _sceneObjects[(uint32)type];
	}

	// ������Ʈ�� ���� �߰����ִ� �Լ�
	void AddObjectToCurrentScene(Object* obj, OBJECT_TYPE type)
	{
		_sceneObjects[(uint32)type].push_back(obj);
		obj->SetOuterScene(this);
		obj->SetOuterSceneType(this->GetOwnSceneType());
	}

	// Ÿ�Կ� ���� ������Ʈ�� �����ϰ� ���� �߰����ִ� �Լ�
	template<typename T>
	Object* CreateAndAppendToScene(OBJECT_TYPE type)
	{
		T* obj = new T;

		_sceneObjects[(uint32)type].push_back(obj);
		obj->SetOuterScene(this);
		obj->SetOuterSceneType(this->GetOwnSceneType());

		return obj;
	}

	// �÷��̾� ������ ���� �߰��� ���ִ� �Լ�
	Object* CreatePlayer()
	{
		return CreateAndAppendToScene<Player>(OBJECT_TYPE::PLAYER);
	}

	// ������� �÷��̾� ��ȯ���ִ� �Լ�
	Player* GetPlayer()
	{
		return static_cast<Player*>(_sceneObjects[(uint32)OBJECT_TYPE::PLAYER].back());
	}

protected:
	// Scene Beginȣ���� ������Ʈ �ʱⰪ ���õ�
	void InitObjects();

protected:
	// Scene����� �� ȣ�� �� �Լ���
	virtual void DeleteAllObjectsByType(OBJECT_TYPE type);
	void DeleteAllObjects();

protected:
	vector<Object*>		_sceneObjects[MAX_LENGH];
	wstring				_sceneName = L"";
	SCENE_TYPE			_sceneType = SCENE_TYPE::END;
};	

