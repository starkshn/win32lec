#include "pch.h"
#include "Object.h"
#include "Collider.h"

Object::Object()
{

}

Object::~Object()
{
	if (nullptr != _colliderComponent)
	{
		delete _colliderComponent;
	}
}

Object::Object(const Object& other)
	:
	_dir(other._dir),
	_centerPos(other._centerPos),
	_type(other._type),
	_state(other._state),
	_patrolType(other._patrolType),
	_rotateType(other._rotateType),
	_speed(other._speed),
	_patrolDistace(other._patrolDistace),
	_colliderComponent(nullptr),
	_outerScene(other._outerScene),
	_outerSceneType(other._outerSceneType),
	_texture(other._texture),
	_objName(other._objName)
{
	_colliderComponent = new Collider(*other._colliderComponent);
	_colliderComponent->SetOuterObject(this);
	_colliderComponent->Init();
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

void Object::CreateCollider()
{
	_colliderComponent = new Collider();
	_colliderComponent->SetOuterObject(GetThis());
	_colliderComponent->Init();
}

void Object::CreateCollider(uint32 textureHeight, uint32 textureWidth, Vec2 textureScale, Vec2 offset)
{
	_colliderComponent = new Collider();
	_colliderComponent->SetOuterObject(GetThis());

	_colliderComponent->SetColliderScale(textureScale);
	_colliderComponent->SetOffset(offset);

	_colliderComponent->Init();
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


void Object::Patrol_Vetical_Horizaon_Sin()
{
	const float _amp = 150.f;		// 진폭
	const float _sp = 300.f;		// 스피드

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

