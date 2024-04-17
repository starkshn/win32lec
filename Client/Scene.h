#pragma once

#include "Object.h"
#include "Player.h"
#include "Rect.h"
#include "Brick.h"
#include "Texture.h"
#include "UI.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void InitScene() abstract;
	virtual void BeginScene() abstract;
	virtual void EndScene() abstract;
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render();

public:
	void CreateTile(uint32 tileXCount, uint32 tileYCount);
	void CheckTileIdx();

public:
	void SetCameraLookAtPos(Vec2 pos)
	{
		CAMERA->SetCameraCurrentLookAtPos(pos);
	}

public:
	void SetName(const wstring& name) { _sceneName = name; }
	const wstring& GetName() { return _sceneName; }

	void SetSceneType(const SCENE_TYPE type) { _sceneType = type; }
	const SCENE_TYPE GetOwnSceneType() { return _sceneType; }

public:
	// Ÿ�Կ� ���� ������Ʈ'��'�� ��ȯ�ϴ� �Լ�
	vector<Object*>& GetObjectsByType(OBJECT_TYPE type) { return _sceneObjects[(uint32)type]; }

	Object* GetObjectByTypeAndIndex(OBJECT_TYPE type, uint32 idx)
	{
		auto vec = GetObjectsByType(type);
		uint32 vecSize = uint32(vec.size());

		// idx�� ���� ���� ����ٸ� assert
		assert(idx < vecSize);

		return vec[idx];
	}

	void PushBackObjectByType(Object* obj, OBJECT_TYPE type)
	{
		_sceneObjects[(uint32)type].push_back(obj);
	}

	Vec2 GetMouseRenderPos() { return _mouseRenderPos; }
	void SetMouseRenderPos(Vec2 renderPos) { _mouseRenderPos = renderPos; }

	Vec2 GetMouseWindowPos() { return _mouseWindowPos; }
	void SetMouseWindowPos(Vec2 windowPos) { _mouseWindowPos = windowPos; }

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

	Vec2 GetCurrentTileXYCount() { return Vec2(float(_tileXCount), float(_tileYCount)); }
	void SetCurrentTileXYCount(Vec2 count) 
	{
		_tileXCount = uint32(count.x);
		_tileYCount = uint32(count.y);
	}

protected:
	// Scene Beginȣ���� ������Ʈ �ʱⰪ ���õ�
	void InitObjects();
	void InitObjectCollision(OBJECT_TYPE ltype, OBJECT_TYPE rtype);
	void ObjectBegin();

public:
	// Scene����� �� ȣ�� �� �Լ���
	virtual void DeleteAllObjectsByType(OBJECT_TYPE type);

protected:
	void DeleteAllObjects();

protected:
	vector<Object*>		_sceneObjects[MAX_LENGH];
	wstring				_sceneName = L"";
	SCENE_TYPE			_sceneType = SCENE_TYPE::END;

protected:
	uint32				_tileXCount = 0;
	uint32				_tileYCount = 0;

private:
	Vec2				_mouseRenderPos = Vec2();
	Vec2				_mouseWindowPos = Vec2();
};	

