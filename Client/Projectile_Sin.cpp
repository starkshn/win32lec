#include "pch.h"
#include "Projectile_Sin.h"

Projectile_Sin::Projectile_Sin()
{
}

Projectile_Sin::~Projectile_Sin()
{
}

Projectile_Sin* Projectile_Sin::Clone()
{
	return new Projectile_Sin(*this);
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
	Projectile::Render();
}

void Projectile_Sin::Init()
{
	Projectile::Init();

	SetSpeed(300.f);
	SetDir(DIR_DOWN);
	SetAmplitude(100.f);
	SetAmplitudeSpeed(400.f);
	SetCenterPos(GetPos());
}

void Projectile_Sin::Begin()
{

}

void Projectile_Sin::End()
{

}
