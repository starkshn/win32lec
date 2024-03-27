#include "pch.h"
#include "Projectile_Cos.h"

Projectile_Cos::Projectile_Cos()
{
}

Projectile_Cos::~Projectile_Cos()
{
}

Projectile_Cos* Projectile_Cos::Clone()
{
	return new Projectile_Cos(*this);
}

void Projectile_Cos::Update()
{
	Vec2 pos = GetPos();
	float angle = GetAngle();

	SetAngle(angle + GetAmplitudeSpeed() * DT_F);
	CHECK_SIN_ANGLE(GetAngle());
	float val = float(cos(RAD(GetAngle()))) * GetAmplitude();
	pos.x = GetCenterPos().x + val;
	pos.y += GetSpeed() * GetDir().y * DT_F * -1;

	SetPos(pos);
}

void Projectile_Cos::Render()
{
	DRAW_RECT();
}

void Projectile_Cos::Init()
{
	Projectile::Init();

	SetAmplitude(100.f);
	SetAmplitudeSpeed(700.f);
	SetCenterPos(GetPos());
}

void Projectile_Cos::Begin()
{
}

void Projectile_Cos::End()
{
}
