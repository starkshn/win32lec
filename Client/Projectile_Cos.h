#pragma once
#include "Projectile.h"

class Projectile_Cos : public Projectile
{
public:
	Projectile_Cos();
	~Projectile_Cos();

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;
};

