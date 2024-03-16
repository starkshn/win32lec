#include "pch.h"
#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	Vec2 pos = GetPos();

	pos += GetSpeed() * GetDir() * DT_F * -1;

	SetPos(pos);
}

void Projectile::Render()
{
	DRAW_CIRCLE();
}

void Projectile::Init()
{
	SetDir(Vec2(0, 1));
	SetSpeed(300.f);
	SetAmplitude(100.f);
	SetAmplitudeSpeed(700.f);
	SetCenterPos(GetPos());
}

void Projectile::Begin()
{

}

void Projectile::End()
{

}
