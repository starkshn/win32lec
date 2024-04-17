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
	// 타입에 따라 오브젝트'들'을 반환하는 함수
	vector<Object*>& GetObjectsByType(OBJECT_TYPE type) { return _sceneObjects[(uint32)type]; }

	Object* GetObjectByTypeAndIndex(OBJECT_TYPE type, uint32 idx)
	{
		auto vec = GetObjectsByType(type);
		uint32 vecSize = uint32(vec.size());

		// idx가 벡터 범위 벗어난다면 assert
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

	Vec2 GetCurrentTileXYCount() { return Vec2(float(_tileXCount), float(_tileYCount)); }
	void SetCurrentTileXYCount(Vec2 count) 
	{
		_tileXCount = uint32(count.x);
		_tileYCount = uint32(count.y);
	}

protected:
	// Scene Begin호출후 오브젝트 초기값 셋팅들
	void InitObjects();
	void InitObjectCollision(OBJECT_TYPE ltype, OBJECT_TYPE rtype);
	void ObjectBegin();

public:
	// Scene변경될 때 호출 될 함수들
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

