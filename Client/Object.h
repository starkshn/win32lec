#pragma once

class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Update() {};
	virtual void Render() {};
	virtual void Init() {};

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

	void SetDir(Vec2 dir) { _dir = dir; }
	const Vec2 GetDir() { return _dir; }

	const OBJECT_STATE GetObjectState() { return _state; }
	void SetObjectState(OBJECT_STATE type) { _state = type; }
	
	const PATROL_TYPE GetPatrolType() { return _patrolType; }
	void SetPatrolType(const PATROL_TYPE type) { _patrolType = type; }

	const ROTATE_TYPE GetRotateType() { return _rotateType; }
	void SetRotateType(const ROTATE_TYPE type) { _rotateType = type; }

public:
	const double GetAngle() { return _angle; }
	void SetAngle(double angle) { _angle = angle; }
	
	const double GetRadian() { return _radian; }
	void SetRadian(double rad) { _radian = rad; }

public:
	void Rotate(double radius);
	void Patrol_Vetical_Horizaon_Sin();
	
public:
	// when OBJECT_TYPE is rectangle can use below functions
	int GetLeft() { return _pos.x - _scale.x / 2; };
	int GetTop() { return _pos.y - _scale.y / 2; };
	int GetRight() { return _pos.x + _scale.x / 2; };
	int GetBottom() { return _pos.y + _scale.y / 2; };

private:
	Vec2 _pos				= { GET_RESOLUTION().x / 2, GET_RESOLUTION().y / 2 };
	Vec2 _scale				= { DEFAULT_X_SCALE, DEFAULT_Y_SCALE };
	Vec2 _patrolCenterPos	= { GET_RESOLUTION().x / 2, GET_RESOLUTION().y / 2 };
	Vec2 _dir				= DEFAULT_DIR;

	OBJECT_TYPE _type			= DEFAULT_OBJECT_TYPE;
	OBJECT_STATE _state			= DEFAULT_OBJECT_STATE;
	PATROL_TYPE _patrolType		= DEFAULT_PATROL_TYPE;
	ROTATE_TYPE _rotateType		= DEFAULT_ROTATE_TYPE;
	OBJECT_PROPERTY _property	= DEFAULT_PROPERTY_TYPE;
	float _speed				= DEFAULT_SPEED;
	float _patrolDistace		= DEFAULT_PATROL_DISTANCE;

private:
	double _angle = 0;
	double _radian = 0;

};

