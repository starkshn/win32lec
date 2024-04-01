#pragma once
#include "Component.h"

class Object;

class Collider : public Component
{
public:
	Collider();
	virtual ~Collider() override;

	Collider(const Collider& other);

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;

public:
	// 고유한 ID 설정
	const uint32 GetID() { return _id; }
	void SetID(uint32 id) { _id = id; }

public:
	// 충돌 발생 여부
	void OnCollision(Collider* other);		// 충돌 중인지
	void OnCollisionEnter(Collider* other); // 충돌 최초로 한지
	void OnCollisionExit(Collider* other);  // 충돌 벗어났는지

private:
	static UINT g_nextID;

private:
	UINT		_id				= 0;
	INT			_isCollision	= 0;
};

