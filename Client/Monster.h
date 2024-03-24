#pragma once
#include "Object.h"
class Monster : public Object
{

public:
	Monster();
	~Monster() override;

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;

public:
	virtual void OnCollision(Collider* otherCollider) override;
	virtual void OnCollisionEnter(Collider* otherCollider) override;
	virtual void OnCollisionExit(Collider* otherCollider) override;

};

