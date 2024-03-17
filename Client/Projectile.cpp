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

	// theta 로 이동
	/*pos.x += GetSpeed() * cosf(GetTheta()) * DT_F;
	pos.y -= GetSpeed() * sinf(GetTheta()) * DT_F;*/

	// 방향벡터로 이동
	pos.x += (GetSpeed() * (GetDir().x) * DT_F);
	pos.y += (GetSpeed() * (GetDir().y) * DT_F);

	// 회전행렬
	/*float theta = 1.0f * DT_F;
	float x = cosf(theta) - sinf(theta);
	float y = sinf(theta) + cosf(theta);*/

	SetPos(pos);
}

void Projectile::Render()
{
	DRAW_CIRCLE();
}

void Projectile::Init()
{
	SetDir(Vec2(1, 1));
	SetSpeed(600.f);
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
