#include "pch.h"
#include "Projectile.h"
#include "Texture.h"
#include "Collider.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	Vec2 pos = GetPos();

	// theta �� �̵�
	/*pos.x += GetSpeed() * cosf(GetTheta()) * DT_F;
	pos.y -= GetSpeed() * sinf(GetTheta()) * DT_F;*/

	// ���⺤�ͷ� �̵�
  	pos.x += (GetSpeed() * (GetDir().x) * DT_F);
	pos.y += (GetSpeed() * (GetDir().y) * DT_F);

	// ȸ�����
	/*float theta = 1.0f * DT_F;
	float x = cosf(theta) - sinf(theta);
	float y = sinf(theta) + cosf(theta);*/

	SetPos(pos);
}

void Projectile::Render()
{
	uint32 h = (int)GetTexture()->GetTexHeight();
	uint32 w = (int)GetTexture()->GetTexWidth();

	Vec2 pos = GetPos();
	int lx = int(pos.x - float(w / 2.f));
	int ly = int(pos.y - float(h / 2.f));

	TransparentBlt
	(
		GET_MEMDC(), int(lx), int(ly), w, h,
		GetTexture()->GetDC(), 0, 0, w, h, RGB(255, 0, 255)
	);

	ComponentRender();
}

void Projectile::Init()
{
	// set player texture
	SetTexture(static_pointer_cast<Texture>(RESOURCE->LoadTexture(L"Missile", L"texture\\test_missile.bmp")));

	CreateCollider();
	auto col = GetCollider();
	int th = GetTexture()->GetTexHeight();
	int tw = GetTexture()->GetTexWidth();
	col->SetColliderScale(Vec2(float(th), float(tw)));
	col->SetOffset(Vec2(float(0), float(0)));

	Vec2 playerPos = GET_PLAYER()->GetPos();
	Vec2 playerScale = GET_PLAYER()->GetScale();

	SetPos(Vec2(playerPos.x, playerPos.y - playerScale.y / 2.f));
	SetScale(Vec2(30.f, 30.f));

	SetDir(DIR_UP);
	SetSpeed(500.f);
}

void Projectile::Begin()
{

}

void Projectile::End()
{

}
