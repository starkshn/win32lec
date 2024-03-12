#pragma once

#include "Object.h"

class Scene : public enable_shared_from_this<Scene>
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void InitScene() abstract;
	virtual void Update();
	virtual void Render();
	virtual void EnterScene() abstract;
	virtual void ExitScene() abstract;

public:
	void SetName(const wstring& name) { _sceneName = name; }
	const wstring& GetName() const { return _sceneName; }
	void SetSceneType(const SCENE_TYPE type) { _sceneType = type; }
	const SCENE_TYPE GetOwnSceneType() { return _sceneType; }

protected:
	template <typename T>
	void AddObject(OBJECT_TYPE type, Vec2 scale, Vec2 pos)
	{
		auto obj = static_pointer_cast<Object>(make_shared<T>());
		_sceneObjects[(uint32)type].push_back(obj);
		_sceneObjects[(uint32)type].back()->SetPos(pos);
		_sceneObjects[(uint32)type].back()->SetScale(scale);
	}

	shared_ptr<Object> GetSceneObject(OBJECT_TYPE type)
	{
		return _sceneObjects[(uint32)type].back();
	}

	void RemoveObject();
	void FindObject();

private:
	vector<shared_ptr<Object>> _sceneObjects[MAX_LENGH];
	wstring		_sceneName;
	SCENE_TYPE	_sceneType;
};

