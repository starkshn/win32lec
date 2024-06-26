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

Projectile* Projectile::Clone()
{
	return new Projectile(*this);
}

void Projectile::Update()
{
	Vec2 pos = GetPos();

	// theta 로 이동
	/*pos.x += GetSpeed() * cosf(GetTheta()) * DT_F;
	pos.y -= GetSpeed() * sinf(GetTheta()) * DT_F;*/

	auto sp = GetSpeed();

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
	Object::Render();
	Vec2 rednerPos = GetRenderPos();

	uint32 h = (int)GetTexture()->GetTexHeight();
	uint32 w = (int)GetTexture()->GetTexWidth();

	Vec2 pos = GetPos();
	/*int lx = int(pos.x - float(w / 2.f));
	int ly = int(pos.y - float(h / 2.f));*/

	int lx = int(rednerPos.x - float(w / 2.f));
	int ly = int(rednerPos.y - float(h / 2.f));

	TransparentBlt
	(
		GET_MEMDC, 
		int(lx), int(ly), 
		w, h,
		GetTexture()->GetDC(), 
		0, 0, w, h, 
		RGB(255, 0, 255)
	);
}

void Projectile::Init()
{
	// Set name
	SetObjectName(L"DefaultProjectile");

	// Set pos, scale, dir, speed
	Object* player = const_cast<Player*>(GET_PLAYER);
	Vec2 playerPos = player->GetPos();
	Vec2 playerScale = player->GetScale();

	SetPos(Vec2(playerPos.x, playerPos.y - playerScale.y / 2.f));
	SetScale(Vec2(30.f, 30.f));
	SetDir(DIR_UP);
	SetSpeed(600.f);

	// Set texture
	SetTexture(static_cast<Texture*>(RESOURCE->LoadTexture(L"Missile", L"texture\\test_missile.bmp")));

	// Create Collider
	Component* comp = CreateComponent<Collider>(COMP_TYPE::COLLIDER);
	int th = GetTexture()->GetTexHeight();
	int tw = GetTexture()->GetTexWidth();
	comp->SetScale(Vec2(float(th), float(tw)));
	comp->SetOffset(Vec2(float(0), float(0)));
}

void Projectile::Begin()
{

}

void Projectile::End()
{

}

void Projectile::OnCollision(Collider* otherCollider)
{

}

void Projectile::OnCollisionEnter(Collider* otherCollider)
{
	Object* otherObject = otherCollider->GetOwnerObject();
	if (otherObject->GetObjectName() == L"DefaultMonster")
	{
		DeleteObject(this);
	}
}

void Projectile::OnCollisionExit(Collider* otherCollider)
{

}
