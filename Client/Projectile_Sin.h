#pragma once
#include "Projectile.h"
class Projectile_Sin : public Projectile
{
public:
	Projectile_Sin();
	~Projectile_Sin();

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;
};

