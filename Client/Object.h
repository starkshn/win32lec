#pragma once

class Scene;

class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Update() 
	{
		
	};
	virtual void Render() 
	{
		Rectangle(GET_MEMDC(), GetLeft(), GetTop(), GetRight(), GetBottom());
	};
	virtual void Init() {};
	virtual void Begin() {};
	virtual void End() {};

public:
	void SetPos(Vec2 pos) { _pos = pos; }
	void SetScale(Vec2 scale) { _scale = scale; }

	const Vec2 GetPos() { return _pos; }
	const Vec2 GetScale() { return _scale; }
	const OBJECT_TYPE GetType() { return _type; }

	const float GetSpeed() { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }

	const OBJECT_PROPERTY GetProperty() { return _property; }
	void SetProperty(OBJECT_PROPERTY type) { _property = type; }

	void SetPatrolCenterPos(Vec2 patrolCentorPos) { _patrolCenterPos = patrolCentorPos; }
	const Vec2 GetPatrolCenterPos() { return _patrolCenterPos;}
	void SetPatrolDistance(float dist) { _patrolDistace = dist; }
	const float GetPatrolDistance() { return _patrolDistace; }

	inline const float GetVectorLength(const Vec2& vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	inline Vec2 Normalize(Vec2 vec)
	{
		float len = GetVectorLength(vec);

		assert(len != 0.f);

		vec.x /= len;
		vec.y /= len;

		return vec;
	}

	const Vec2 GetDir() { return _dir; }

	void SetDir(Vec2 dir)
	{
		_dir = Normalize(dir);
		_dir.y *= -1;
	}
	void SetTheta(float theta) { _theta = theta; }
	const float GetTheta() { return _theta; }

	const OBJECT_STATE GetObjectState() { return _state; }
	void SetObjectState(OBJECT_STATE type) { _state = type; }
	
	const PATROL_TYPE GetPatrolType() { return _patrolType; }
	void SetPatrolType(const PATROL_TYPE type) { _patrolType = type; }

	const ROTATE_TYPE GetRotateType() { return _rotateType; }
	void SetRotateType(const ROTATE_TYPE type) { _rotateType = type; }

public:
	const float GetAngle() { return _angle; }
	void SetAngle(float angle) { _angle = angle; }
	
	const float GetRadian() { return _radian; }
	void SetRadian(float rad) { _radian = rad; }

public:
	void Rotate(float radius);
	void Patrol_Vetical_Horizaon_Sin();

public:
	void SetOuterScene(weak_ptr<Scene> scene) { _outerScene = scene; }
	const shared_ptr<Scene> GetOuterScene() { return _outerScene.lock();  }

	void SetOuterSceneType(SCENE_TYPE type) { _outerSceneType = type; }
	const SCENE_TYPE GetOuterSceneType() { return _outerSceneType; }

	void SetRotateSpeed(float speed) { _rotateSpeed = speed; }
	const float GetRotateSpeed() { return _rotateSpeed; }

	void SetCenterPos(Vec2 centerPos) { _centerPos = centerPos; }
	const Vec2 GetCenterPos() { return _centerPos; }

	const float GetAmplitude() { return _amplitude; }
	void SetAmplitude(float amplitude) { _amplitude = amplitude; }

	const float GetAmplitudeSpeed() { return _amplitudeSpeed;}
	void SetAmplitudeSpeed(float speed) { _amplitudeSpeed = speed; }
	
public:
	// when OBJECT_TYPE is rectangle can use below functions
	int GetLeft() { return int(_pos.x - _scale.x / 2); };
	int GetTop() { return int(_pos.y - _scale.y / 2); };
	int GetRight() { return int(_pos.x + _scale.x / 2); };
	int GetBottom() { return int(_pos.y + _scale.y / 2); };

private:
	Vec2 _pos				= { float(GET_RESOLUTION().x / 2), float(GET_RESOLUTION().y / 2) };
	Vec2 _scale				= { DEFAULT_X_SCALE, DEFAULT_Y_SCALE };
	Vec2 _patrolCenterPos	= { float(GET_RESOLUTION().x / 2), float(GET_RESOLUTION().y / 2) };
	Vec2 _dir				= DEFAULT_DIR;
	Vec2 _centerPos;

	OBJECT_TYPE _type			= DEFAULT_OBJECT_TYPE;
	OBJECT_STATE _state			= DEFAULT_OBJECT_STATE;
	PATROL_TYPE _patrolType		= DEFAULT_PATROL_TYPE;
	ROTATE_TYPE _rotateType		= DEFAULT_ROTATE_TYPE;
	OBJECT_PROPERTY _property	= DEFAULT_PROPERTY_TYPE;
	float _speed				= DEFAULT_SPEED;
	float _patrolDistace		= DEFAULT_PATROL_DISTANCE;

private:
	float _angle = 0.f;
	float _radian = 0.f;
	float _rotateSpeed = 0.f;
	float _amplitude = 0.f;
	float _amplitudeSpeed = 0.f;
	float _theta = 0.f;


private:
	weak_ptr<Scene> _outerScene;
	SCENE_TYPE _outerSceneType;
};

