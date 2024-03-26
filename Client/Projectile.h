#pragma once
#include "Object.h"
class Projectile : public Object
{
public:
	Projectile();
	~Projectile();
	
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
	
private:
	
};

