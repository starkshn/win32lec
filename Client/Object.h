#pragma once

class Scene;
class Collider;

class Texture;

class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Update() 
	{
		
	};

	virtual void FinalUpdate() final;
	virtual void Render();
	void ComponentRender();
	virtual void Init() {};
	virtual void Begin() {};
	virtual void End() {};

public:
	Object* GetThis()
	{
		return this;
	}

public:
	// scene ���� ������Ʈ ���� ��ü
	// TODO GetOuterScene �޴��ʿ��� �����ؾ��� ���ϴ�??
	const Scene* GetOuterScene()
	{
		return _outerScene;
	}

	void SetOuterScene(Scene* outetScene) 
	{ 
		_outerScene = outetScene; 
	}


	// scene type
	const SCENE_TYPE GetOuterSceneType() 
	{ 
		return _outerSceneType; 
	}

	void SetOuterSceneType(SCENE_TYPE type) 
	{ 	
		_outerSceneType = type; 
	}

	// texture
	Texture* GetTexture() 
	{ 
		return _texture;
	}

	void SetTexture(Texture* tex) 
	{ 
		_texture = tex;
	}

	// collider
	void CreateCollider();

	Collider* GetCollider() 
	{ 
		return _colliderComponent; 
	}

	void SetCollider(Collider* collider)
	{
		_colliderComponent = collider;
	}

	// name
	const wstring& GetObjectName()
	{
		return _objName;
	}

	void SetObjectName(const wstring& name)
	{
		_objName = name;
	}

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

	// �Ӽ�
	const OBJECT_PROPERTY GetProperty() 
	{ 
		return _property; 
	}

	void SetProperty(OBJECT_PROPERTY type) 
	{ 
		_property = type;
	}

	// obj state
	const OBJECT_STATE GetObjectState() { return _state; }
	void SetObjectState(OBJECT_STATE type) 
	{ 
		_state = type;
	}

	// ��Ʈ�� Ÿ��
	const PATROL_TYPE GetPatrolType() 
	{ return _patrolType; }

	void SetPatrolType(const PATROL_TYPE type) { _patrolType = type; }

	// ȸ�� Ÿ��
	const ROTATE_TYPE GetRotateType() 
	{ return _rotateType; }

	void SetRotateType(const ROTATE_TYPE type) { _rotateType = type; }

	// ���� 
	const Vec2 GetDir() { return _dir; }
	void SetDir(Vec2 dir) 
	{
		_dir = Normalize(dir);
		_dir.y *= -1;
	}

	// ��Ÿ
	const float GetTheta() 
	{ 
		return _theta; 
	}

	void SetTheta(float theta) 
	{ 
		_theta = theta; 
	}

	// 60�й� ����
	const float GetAngle() 
	{ 
		return _angle; 
	}

	void SetAngle(float angle) 
	{ 
		_angle = angle; 
	}

	// ����
	const float GetRadian() 
	{ 
		return _radian; 
	}

	void SetRadian(float rad) 
	{ 
		_radian = rad; 
	}

	// ��Ʈ�� �߾� ��ġ
	void SetPatrolCenterPos(Vec2 patrolCentorPos) 
	{ 
		_patrolCenterPos = patrolCentorPos; 
	}

	const Vec2 GetPatrolCenterPos() 
	{ 
		return _patrolCenterPos;
	}

	// ��Ʈ�� �Ÿ�
	void SetPatrolDistance(float dist) 
	{
		_patrolDistace = dist; 
	}

	const float GetPatrolDistance() 
	{ 
		return _patrolDistace;
	}

	// ȸ�� �ӵ�
	void SetRotateSpeed(float speed) 
	{ 
		_rotateSpeed = speed; 
	
	}
	const float GetRotateSpeed() 
	{ 
		return _rotateSpeed; 
	}

	// ������Ʈ �߾���
	void SetCenterPos(Vec2 centerPos) 
	{ 
		_centerPos = centerPos;
	}

	const Vec2 GetCenterPos() 
	{ 
		return _centerPos;
	}

	// ���� ��
	const float GetAmplitude() 
	{ 
		return _amplitude;
	
	}
	void SetAmplitude(float amplitude) 
	{ 
		_amplitude = amplitude; 
	}

	// ���� �̵� �ӵ�
	const float GetAmplitudeSpeed()
	{ 
		return _amplitudeSpeed; 
	}

	void SetAmplitudeSpeed(float speed) 
	{ 
		_amplitudeSpeed = speed;
	}

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

	// �浹
public:
	virtual void OnCollision(Collider* otherCollider) {};
	virtual void OnCollisionEnter(Collider* otherCollider) {};
	virtual void OnCollisionExit(Collider* otherCollider) {};
	
public:
	// when OBJECT_TYPE is rectangle can use below functions
	int GetLeft() { return int(_pos.x - _scale.x / 2); };
	int GetTop() { return int(_pos.y - _scale.y / 2); };
	int GetRight() { return int(_pos.x + _scale.x / 2); };
	int GetBottom() { return int(_pos.y + _scale.y / 2); };

private:
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

	OBJECT_TYPE _type			= DEFAULT_OBJECT_TYPE;
	OBJECT_STATE _state			= DEFAULT_OBJECT_STATE;
	PATROL_TYPE _patrolType		= DEFAULT_PATROL_TYPE;
	ROTATE_TYPE _rotateType		= DEFAULT_ROTATE_TYPE;
	OBJECT_PROPERTY _property	= DEFAULT_PROPERTY_TYPE;
	float _speed				= DEFAULT_SPEED;
	float _patrolDistace		= DEFAULT_PATROL_DISTANCE;

private:
	float _angle				= 0.f;
	float _radian				= 0.f;
	float _rotateSpeed			= 0.f;
	float _amplitude			= 0.f;
	float _amplitudeSpeed		= 0.f;
	float _theta				= 0.f;

	// collider
private:
	// collider������ Object�� weak_ptr�� �������ش�.
	Collider*			_colliderComponent;
	
private:
	Scene*				_outerScene;
	SCENE_TYPE			_outerSceneType;

	// ���ҽ� �Ŵ����κ��� �����ϰ� �ִ� ���ҽ�������, ���ҽ� �Ŵ����� ���� ��ü�� Object�� ����ų ���� ���� ������ shared_ptr�� �������ش�.
	Texture*			_texture;
	wstring				_objName;
};			

