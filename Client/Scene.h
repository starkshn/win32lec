#pragma once

#include "Object.h"
#include "Player.h"
#include "Rect.h"
#include "Brick.h"

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
	shared_ptr<T> AddObject(OBJECT_TYPE type, Vec2 pos, Vec2 scale)
	{
		static_assert(std::is_base_of<Object, T>::value, "T type is not Object Type!");

		auto obj = static_pointer_cast<Object>(make_shared<T>());

		_sceneObjects[(uint32)type].push_back(obj);
		_sceneObjects[(uint32)type].back()->SetPos(pos);
		_sceneObjects[(uint32)type].back()->SetScale(scale);

		return static_pointer_cast<T>(obj);
	}

	template <typename T>
	shared_ptr<T> GetSceneObject(OBJECT_TYPE type)
	{
		return _sceneObjects[(uint32)type].back();
	}

	template <typename T>
	shared_ptr<T> SpawnStaticObject(OBJECT_TYPE type = OBJECT_TYPE::RECTANGLE, OBJECT_STATE state = OBJECT_STATE::DEFAULT, Vec2 pos = Vec2(250.f, 250.f), Vec2 scale = Vec2(50.f, 50.f), float speed = 0.f)
	{
		auto obj = AddObject<T>(type, pos, scale);

		if (state != OBJECT_STATE::DEFAULT)
		{
			obj->SetSpeed(speed);
			obj->SetProperty(OBJECT_PROPERTY::DYNAMIC);

			switch (state)
			{
			case OBJECT_STATE::DEFAULT:
				{
					
				}
				break;
			case OBJECT_STATE::PATROL:
				{
					obj->SetObjectState(OBJECT_STATE::PATROL);
					obj->SetDir(Vec2(1, 0));
					obj->SetPatrolCenterPos(obj->GetPos());
					obj->SetPatrolDistance(DEFAULT_PATROL_DISTANCE);
				}
				break;
			case OBJECT_STATE::ROTATE:
				{
					obj->SetObjectState(OBJECT_STATE::ROTATE);
				}
				break;
			default:
				break;
			}
		}

		obj->Init();
		return obj;
	}

	template <typename T>
	shared_ptr<T> SpawnDynamicObject(OBJECT_TYPE type = OBJECT_TYPE::RECTANGLE, OBJECT_STATE state = OBJECT_STATE::PATROL, Vec2 pos = Vec2(250.f, 250.f), Vec2 scale = Vec2(50.f, 50.f), float speed = 50.f)
	{
		return SpawnStaticObject<T>(type, state, pos, scale, speed);
	}

	template <typename T>
	shared_ptr<T> SpawnDynamicObject_AlignVertical()
	{
		return shared_ptr<T>();
	}

	void CreatePlayer(Vec2 startPos, Vec2 scale)
	{
		AddObject<Player>(OBJECT_TYPE::PLAYER, startPos, scale);
	}

protected:
	void RemoveObject();
	void FindObject();

private:
	vector<shared_ptr<Object>> _sceneObjects[MAX_LENGH];
	wstring		_sceneName;
	SCENE_TYPE	_sceneType;
};

