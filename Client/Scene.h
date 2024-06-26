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
	// 수업 랜더링 100~105 FPS
	void RenderObject();

	// 내가 만든 렌더링 90~100 FPS
	void RenderObjectMy();

protected:
	virtual void UpdateTextOfGameInfo();
	virtual void RenderTextOfGameInfo();

protected:
	virtual void UpdateSceneKeyInput() abstract;

public:
	void CreateTile(uint32 tileXCount, uint32 tileYCount);
	void CheckTileIdx();


	// Render Optimization
private:
	// 수업 때 만든 Tile Optimization
	void RenderTile();

	// 내가 만든 Tile Optimization (70~80 FPS정도)
	bool TileRenderOptimization(Object& tile);

	//	오브젝트용 Render Optimization
	bool ObjectRenderOptimization(Object& object);

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
	const vector<Object*>& GetObjectsByType(OBJECT_TYPE type) { return _sceneObjects[(uint32)type]; }
	
	vector<Object*>& GetUIObjects() 
	{ 
		return _sceneObjects[(uint32)OBJECT_TYPE::UI];
	}

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

	// Object <-> Mouse
public:
	Object* GetCurMouseHoverObject() 
	{ 
		return _curHoverOnObject;
	}
	void SetCurMouseHoverObject(Object* obj) 
	{ 
		_curHoverOnObject = obj;
	}

	wstring GetCurMouseHoverObjectName() { return _curHoverOnObjectName; }
	void	SetCurMouseHoverObjectName(const WCHAR* objName) 
	{
		_curHoverOnObjectName = objName;
	}

	// Mouse RenderPos
public:
	Vec2 GetMouseRenderPos() { return _mouseRenderPos; }
	void SetMouseRenderPos(Vec2 renderPos) { _mouseRenderPos = renderPos; }

	Vec2 GetMouseWindowPos() { return _mouseWindowPos; }
	void SetMouseWindowPos(Vec2 windowPos) { _mouseWindowPos = windowPos; }

	// Add Object To cur Scene
public:
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

	uint32 GetSceneAllObjectCount()
	{
		uint32 count = 0;
		for (uint32 i = 0; i < MAX_LENGH; ++i)
		{
			count += uint32(_sceneObjects[i].size());
		}
		return count;
	}

	// Object <-> Mouse
public:
	Object* GetMouseHoverOnObject() { return _curMouseHoverOnObject; }
	void SetMouseHoverOnObject(Object* obj) { _curMouseHoverOnObject = obj; }
	
	Object* GetMouseLBTNDownObject() { return _curMouseLBTNDownObject; }
	void SetMouseLBTNDownObject(Object* obj) { _curMouseLBTNDownObject = obj; }

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
	virtual void ResetSceneInfo();

	// FILE
public:
	void LoadTile(const wstring& relativePath);

protected:
	vector<Object*>		_sceneObjects[MAX_LENGH];
	wstring				_sceneName = L"";
	SCENE_TYPE			_sceneType = SCENE_TYPE::END;

protected:
	vector<wstring>		_vecGameInfoTexts;

protected:
	uint32				_tileXCount = 0;
	uint32				_tileYCount = 0;

private:
	Vec2				_mouseRenderPos = Vec2();
	Vec2				_mouseWindowPos = Vec2();

private:
	Object*				_curHoverOnObject;
	wstring				_curHoverOnObjectName;

	// Object <-> Mouse
private:
	Object*				_curMouseHoverOnObject	= nullptr;
	Object*				_curMouseLBTNDownObject = nullptr;
};	

