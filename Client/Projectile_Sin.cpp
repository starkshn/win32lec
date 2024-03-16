#include "pch.h"
#include "Projectile_Sin.h"

Projectile_Sin::Projectile_Sin()
{
}

Projectile_Sin::~Projectile_Sin()
{
}

void Projectile_Sin::Update()
{
	Vec2 pos = GetPos();
	float angle = GetAngle();

	SetAngle(angle + GetAmplitudeSpeed() * DT_F);
	CHECK_SIN_ANGLE(GetAngle());
	float val = float(sin(RAD(GetAngle()))) * GetAmplitude();
	pos.x = GetCenterPos().x + val;
	pos.y += GetSpeed() * GetDir().y * DT_F * -1;

	SetPos(pos);
}

void Projectile_Sin::Render()
{
	DRAW_RECT();
}

void Projectile_Sin::Init()
{
	Projectile::Init();
}

void Projectile_Sin::Begin()
{
}

void Projectile_Sin::End()
{
}
