#pragma once

#include "Collider.h"
#include "Animator.h"

// forward declrations...
class Component;
class Texture;
class Scene;

class Object
{
public:
	Object();
	virtual ~Object();
	Object(const Object& other);

	// ���� ������ ��ȯ�ϴ� �Լ�
	virtual Object* Clone() abstract;

	// �Ʒ� �Լ����� ������� �� Tick���� �߻��ϴ� �Լ����̴�.
public:
	// ������Ʈ�鿡 ���� ������Ʈ (��ǥ, ����)
	virtual void Update() {};

	// Component�鿡 ���� ������Ʈ
	virtual void FinalUpdate();

	// ���� ������ �Լ� (Texture etc...)
	// �̰����� Component Render�� ���� ������
	// Object�� ��ӹ޴� ��ü���� Object::Render�� ȣ���ؾ���
	virtual void Render();

	// ������Ʈ ������ (Collider �浹���� ����, ���� �ִϸ��̼� ���)
	void ComponentRender();

public:
	// ������Ʈ �ʱ�ȭ �Լ�
	virtual void Init() {};

	// �� ����/Ż�� �� ȣ��Ǵ� ������Ʈ �Լ�
	virtual void Begin() {};
	virtual void End() {};

public:
	Object* GetThis() { return this; }
	void	CheckMouseHoverOnThisObject();

public:
	template <typename T>
	T* CreateComponent(COMP_TYPE type)
	{
		T* newComp = (new T);
		newComp->SetOwnerObject(this);
		AddComponent(newComp, type);
		return newComp;
	}

	template <typename T>
	void AddComponent(T* comp, COMP_TYPE type)
	{
		_vecComponents[(uint32)type] = static_cast<Component*>(comp);
	}
	
	const bool CheckCompIsValid(COMP_TYPE type) const
	{
		if (GetComponent(type)) return true;
		else return false;
	}

	// �ܼ� ���� ��ȯ
	Component* GetComponent(COMP_TYPE type) const
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

	// �浹
public:
	virtual void OnCollision(Collider* otherCollider) {};
	virtual void OnCollisionEnter(Collider* otherCollider) {};
	virtual void OnCollisionExit(Collider* otherCollider) {};

public:
	// �̺�Ʈ �Ŵ��������� ������ ���θ� ��ȯ�ϴ� �Լ�
	bool GetThisObjectWillDelete() { return deleteObject;}

private:
	// �̺�Ʈ �Ŵ����� ���ؼ� friend�� ���.
	void SetThisObjectWillDelete() { deleteObject = true; }
	friend class EventManager;

	// Get Set
public:
	// scene
	Scene* GetOuterScene() { return _outerScene; }
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

	// RenderPos
	Vec2 GetRenderPos() { return _renderPos; }
	void SetRenderPos(Vec2 pos) { _renderPos = pos; }

	// scale
	const Vec2 GetScale() { return _scale; }
	void SetScale(Vec2 scale) { _scale = scale; }

	// type
	const OBJECT_TYPE GetType() { return _type; }
	void SetType(OBJECT_TYPE type) { _type = type; }

	// speed
	const float GetSpeed() { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }

	// ���� 
	const Vec2 GetDir() { return _dir; }
	void SetDir(Vec2 dir) 
	{
		_dir = Normalize(dir);
		_dir.y *= -1;
	}

	// ��Ÿ
	const float GetTheta() { return _theta; }
	void SetTheta(float theta) { _theta = theta; }

	// 60�й� ����
	const float GetAngle() { return _angle; }
	void SetAngle(float angle) { _angle = angle; }

	// ����
	const float GetRadian() { return _radian; }
	void SetRadian(float rad) { _radian = rad; }

	// ��Ʈ�� �߾� ��ġ
	void SetPatrolCenterPos(Vec2 patrolCentorPos) { _patrolCenterPos = patrolCentorPos; }
	const Vec2 GetPatrolCenterPos() { return _patrolCenterPos; }

	
	// ȸ�� �ӵ�
	void SetRotateSpeed(float speed)  { _rotateSpeed = speed; }
	const float GetRotateSpeed() { return _rotateSpeed; }
	
	// ������Ʈ �߾���
	void SetCenterPos(Vec2 centerPos) { _centerPos = centerPos; }
	const Vec2 GetCenterPos() { return _centerPos; }

	// ���� ��
	const float GetAmplitude() { return _amplitude; }
	void SetAmplitude(float amplitude) { _amplitude = amplitude; }

	// ���� �̵� �ӵ�
	const float GetAmplitudeSpeed() { return _amplitudeSpeed; }
	void SetAmplitudeSpeed(float speed) { _amplitudeSpeed = speed; }

	// ���� ����
	inline const float GetVectorLength(const Vec2& vec) 
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	// ���� ����ȭ
	inline Vec2 Normalize(Vec2 vec)
	{
		float len = GetVectorLength(vec);

		assert(len != 0.f);

		vec.x /= len;
		vec.y /= len;

		return vec;
	}

public:
	// ������Ʈ ȸ��
	void Rotate(float radius);

	// ������Ʈ sin�׷��� ���� ��Ʈ��
	void Patrol_Vetical_Horizaon_Sin();
	
public:
	// when OBJECT_TYPE is rectangle can use below functions
	int GetLeft() { return int(_pos.x - _scale.x / 2); };
	int GetTop() { return int(_pos.y - _scale.y / 2); };
	int GetRight() { return int(_pos.x + _scale.x / 2); };
	int GetBottom() { return int(_pos.y + _scale.y / 2); };

public:
	virtual void UpdateMouseInteraction();

	// UI �� ���� ����� �����ؾ� �ϱ⶧���� �����Լ��� ����
	virtual bool GetMouseHoverOnThisObject() { return _mouseHoverOnThisObject; }
	virtual void SetMouseHoverOnThisObject(bool hoverOn) { _mouseHoverOnThisObject = hoverOn; }

	bool GetMouseLBTNDownOnThisObject() { return _mouseLBTNDownOnThisObject; }
	void SetMouseLBTNDownOnThisObject(bool lbtnDown) { _mouseLBTNDownOnThisObject = lbtnDown; }

private:
	// delete ����
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

	Vec2		_dir				= DEFAULT_DIR;
	Vec2		_centerPos			= Vec2(0.f, 0.f);
	OBJECT_TYPE	_type				= DEFAULT_OBJECT_TYPE;
	Vec2		_renderPos			= Vec2(0.f, 0.f);
	float		_speed				= DEFAULT_SPEED;

private:
	// ��� ������Ʈ Ŭ���� �����ϴ� ���� (Collider ����)
	vector<Component*> _vecComponents;

private:
	// TODO
	// ������Ʈ�� ���� �� �κ�
	float _angle				= 0.f;
	float _radian				= 0.f;
	float _rotateSpeed			= 0.f;
	float _amplitude			= 0.f;
	float _amplitudeSpeed		= 0.f;
	float _theta				= 0.f;

private:
	Scene*		_outerScene			= nullptr;
	SCENE_TYPE	_outerSceneType		= SCENE_TYPE::END;

	// ���ҽ� �Ŵ����κ��� �����ϰ� �ִ� ���ҽ�������, ���ҽ� �Ŵ����� ���� ��ü�� Object�� ����ų ���� ���� ������ shared_ptr�� �������ش�.

	// pTexture�� ��� ���� �ִϸ��̼��� �ֱ� ������ ��� ������ ��� ���� �ʿ�� ����.
	Texture*	_texture			= nullptr;
	wstring		_objName			= L"";

	// mouse 
private:
	bool _mouseHoverOnThisObject	= false;
	bool _mouseLBTNDownOnThisObject = false;
};			

