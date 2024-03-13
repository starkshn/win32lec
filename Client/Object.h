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

	void SetPatrolCenterPos(Vec2 patrolCentorPos) { _patrolCenterPos = patrolCentorPos; }
	const Vec2 GetPatrolCenterPos() { return _patrolCenterPos;}
	void SetPatrolDistance(float dist) { _patrolDistace = dist; }
	const float GetPatrolDistance() { return _patrolDistace; }

	void SetDir(Vec2 dir) { _dir = dir; }
	const Vec2 GetDir() { return _dir; }
	
public:
	// when OBJECT_TYPE is rectangle can use below functions
	int GetLeft() { return _pos.x - _scale.x / 2; };
	int GetTop() { return _pos.y - _scale.y / 2; };
	int GetRight() { return _pos.x + _scale.x / 2; };
	int GetBottom() { return _pos.y + _scale.y / 2; };

private:
	Vec2 _pos = { GET_RESOLUTION().x, GET_RESOLUTION().y };
	Vec2 _scale = {100.f, 100.f};
	OBJECT_TYPE _type = OBJECT_TYPE::RECTANGLE;
	OBJECT_PROPERTY _property = OBJECT_PROPERTY::STATIC;
	float _speed = 0.f;

	Vec2 _patrolCenterPos = {};
	float _patrolDistace = 0.f;
	Vec2 _dir = {};
};

