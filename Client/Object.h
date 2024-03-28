#pragma once

#include "Component.h"
#include "Collider.h"
#include "Animator.h"

class Texture;
class Scene;

class Object
{
public:
	Object();
	virtual ~Object();
	Object(const Object& other);

	// 복사 생성자 반환하는 함수
	virtual Object* Clone() abstract;

public:
	virtual void Update() {};
	virtual void FinalUpdate() final; // 부모가 마지막
	virtual void Render();
	void ComponentRender();
	virtual void Init() {};
	virtual void Begin() {};
	virtual void End() {};

public:
	Object* GetThis() { return this; }

public:
	template <typename T>
	Component* CreateComponent(COMP_TYPE type)
	{
		Component* newComp = static_cast<Component*>(new T);
		newComp->SetOwnerObject(this);
		_vecComponents[(uint32)type] = newComp;
		return newComp;
	}

	const Component* GetComponent(COMP_TYPE type)
	{
		if (nullptr != _vecComponents[(uint32)type])
			return _vecComponents[(uint32)type];
		else return nullptr;
	}

	Collider* GetCollider() const
	{
		if (nullptr != _vecComponents[(uint32)COMP_TYPE::COLLIDER])
		{
			return static_cast<Collider*>(_vecComponents[(uint32)COMP_TYPE::COLLIDER]);
		}
		else return nullptr;
	}

	Animator* GetAnimator() const
	{
		if (nullptr != _vecComponents[(uint32)COMP_TYPE::ANIMATOR])
		{
			return static_cast<Animator*>(_vecComponents[(uint32)COMP_TYPE::ANIMATOR]);
		}
		else return nullptr;
	}

	// 충돌
public:
	virtual void OnCollision(Collider* otherCollider) {};
	virtual void OnCollisionEnter(Collider* otherCollider) {};
	virtual void OnCollisionExit(Collider* otherCollider) {};

public:
	// 이벤트 매니저에의해 삭제될 여부를 반환하는 함수
	const bool GetThisObjectWillDelete() { return deleteObject;}

private:
	// 이벤트 매니저에 한해서 friend로 등록.
	void SetThisObjectWillDelete() { deleteObject = true; }
	friend class EventManager;

	// Get Set
public:
	// scene
	const Scene* GetOuterScene() { return _outerScene; }
	void SetOuterScene(Scene* outetScene) { _outerScene = outetScene; }
	const SCENE_TYPE GetOuterSceneType() { return _outerSceneType; }
	void SetOuterSceneType(SCENE_TYPE type) { _outerSceneType = type; }

	// Texture
	Texture* GetTexture() 
	{ 
		if (nullptr != _texture)
			return _texture;
		else
			return nullptr;
	}
	void SetTexture(Texture* tex) { _texture = tex; }

	// name
	const wstring& GetObjectName(){ return _objName; }
	void SetObjectName(const wstring& name) { _objName = name; }

	// pos
	const Vec2 GetPos() { return _pos; }
	void SetPos(Vec2 pos) { _pos = pos; }

	// scale
	const Vec2 GetScale() { return _scale; }
	void SetScale(Vec2 scale) { _scale = scale; }

	// type
	const OBJECT_TYPE GetType() { return _type; }
	void SetType(OBJECT_TYPE type) { _type = type; }

	// speed
	const float GetSpeed() { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }

	// 방향 
	const Vec2 GetDir() { return _dir; }
	void SetDir(Vec2 dir) 
	{
		_dir = Normalize(dir);
		_dir.y *= -1;
	}

	// 세타
	const float GetTheta() { return _theta; }
	void SetTheta(float theta) { _theta = theta; }

	// 60분법 각도
	const float GetAngle() { return _angle; }
	void SetAngle(float angle) { _angle = angle; }

	// 라디안
	const float GetRadian() { return _radian; }
	void SetRadian(float rad) { _radian = rad; }

	// 패트롤 중앙 위치
	void SetPatrolCenterPos(Vec2 patrolCentorPos) { _patrolCenterPos = patrolCentorPos; }
	const Vec2 GetPatrolCenterPos() { return _patrolCenterPos; }

	
	// 회전 속도
	void SetRotateSpeed(float speed)  { _rotateSpeed = speed; }
	const float GetRotateSpeed() { return _rotateSpeed; }
	
	// 오브젝트 중앙점
	void SetCenterPos(Vec2 centerPos) { _centerPos = centerPos; }
	const Vec2 GetCenterPos() { return _centerPos; }

	// 진폭 값
	const float GetAmplitude() { return _amplitude; }
	void SetAmplitude(float amplitude) { _amplitude = amplitude; }

	// 진폭 이동 속도
	const float GetAmplitudeSpeed() { return _amplitudeSpeed; }
	void SetAmplitudeSpeed(float speed) { _amplitudeSpeed = speed; }

	// 벡터 길이
	inline const float GetVectorLength(const Vec2& vec) 
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	// 벡터 정규화
	inline Vec2 Normalize(Vec2 vec)
	{
		float len = GetVectorLength(vec);

		assert(len != 0.f);

		vec.x /= len;
		vec.y /= len;

		return vec;
	}

public:
	// 오브젝트 회전
	void Rotate(float radius);

	// 오브젝트 sin그래프 따라 패트롤
	void Patrol_Vetical_Horizaon_Sin();
	
public:
	// when OBJECT_TYPE is rectangle can use below functions
	int GetLeft() { return int(_pos.x - _scale.x / 2); };
	int GetTop() { return int(_pos.y - _scale.y / 2); };
	int GetRight() { return int(_pos.x + _scale.x / 2); };
	int GetBottom() { return int(_pos.y + _scale.y / 2); };

private:
	// delete 여부
	bool deleteObject = false;

	Vec2 _pos = 
	{ 
		float(GET_RESOLUTION.x / 2),
		float(GET_RESOLUTION.y / 2)
	};

	Vec2 _scale = 
	{ 
		DEFAULT_X_SCALE, DEFAULT_Y_SCALE 
	};

	Vec2 _patrolCenterPos = 
	{ 
		float(GET_RESOLUTION.x / 2),
		float(GET_RESOLUTION.y / 2)
	};

	Vec2 _dir					= DEFAULT_DIR;
	Vec2 _centerPos;
	OBJECT_TYPE	_type			= DEFAULT_OBJECT_TYPE;
	float _speed				= DEFAULT_SPEED;

private:
	// 모든 컴포넌트 클래스 관리하는 벡터 (Collider 포험)
	vector<Component*> _vecComponents;

private:
	// TODO
	// 컴포넌트로 따로 뺄 부분
	float _angle				= 0.f;
	float _radian				= 0.f;
	float _rotateSpeed			= 0.f;
	float _amplitude			= 0.f;
	float _amplitudeSpeed		= 0.f;
	float _theta				= 0.f;

private:
	Scene*		_outerScene			= nullptr;
	SCENE_TYPE	_outerSceneType		= SCENE_TYPE::END;

	// 리소스 매니저로부터 관리하고 있는 리소스이지만, 리소스 매니저의 실제 객체는 Object를 가르킬 일이 없기 때문에 shared_ptr로 관리해준다.
	Texture*	_texture			= nullptr;
	wstring		_objName			= L"";
};			

