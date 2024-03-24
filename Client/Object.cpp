#include "pch.h"
#include "Object.h"
#include "Collider.h"

Object::Object()
{

}

Object::~Object()
{

}

void Object::FinalUpdate()
{
	auto col = GetCollider();
	if (nullptr != col)
	{
		col->FinalUpdate();
	}
}

void Object::Render()
{
	Rectangle(GET_MEMDC, GetLeft(), GetTop(), GetRight(), GetBottom());

	ComponentRender();
}

void Object::ComponentRender()
{
	auto col = GetCollider();
	if (nullptr != col)
	{
		col->Render();
	}
}

void Object::Rotate(float radius)
{
	auto pos = GetPos();
	SetAngle(GetAngle() + GetSpeed() * DT_F);

	CHECK_SIN_ANGLE(GetAngle());

	float cosVal = float(cos(RAD(GetAngle())) * radius);
	float sinVal = float(sin(RAD(GetAngle())) * radius);
	
	pos.x = GetPatrolCenterPos().x + cosVal;
	pos.y = GetPatrolCenterPos().y + sinVal;
	
	SetPos(pos);
}

const float _amp = 150.f; // 진폭
const float _sp = 300.f; // 스피드

void Object::Patrol_Vetical_Horizaon_Sin()
{
	auto pos = GetPos();
	pos.x += float(GetSpeed() * GetDir().x * DT_F);
	float dis = abs(GetPatrolCenterPos().x - pos.x) - GetPatrolDistance();

	// y axis -> sin
	SetAngle(GetAngle() + DT_F * _sp);
	pos.y = (-1 * float(sin(RAD(GetAngle()))) * _amp) + GetPatrolCenterPos().y;

	// x축 방향전환시
	if (0.f < dis)
	{
		SetDir(GetDir() * -1);
		pos.x += dis * GetDir().x;
	}

	// 60분법 각도가 360도를 넘는경우
	if (GetAngle() > 360)
	{
		auto dis = GetAngle() - 360;
		SetAngle(GetAngle() - dis);
		SetAngle(0);
	}

	SetPos(pos);
}


void Object::CreateCollider()
{
	_colliderComponent = new Collider();
	_colliderComponent->SetOuterObject(GetThis());
}
