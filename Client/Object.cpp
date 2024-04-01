#include "pch.h"
#include "Object.h"
#include "Collider.h"

Object::Object()
{
	// ������Ʈ resize
	_vecComponents.resize((uint32)COMP_TYPE::END);
}

Object::~Object()
{
	// ������Ʈ�� ��� �ִ� ��� ������Ʈ �� Delete
	DeleteObjectsSafe<Component*>(_vecComponents);
}

Object::Object(const Object& other)
	:
	_dir(other._dir),
	_centerPos(other._centerPos),
	_type(other._type),
	_speed(other._speed),
	_outerScene(other._outerScene),
	_outerSceneType(other._outerSceneType),
	_texture(other._texture),
	_objName(other._objName)
{
	// Collider ���� ����
	if (other.CheckCompIsValid(COMP_TYPE::COLLIDER))
	{
		_vecComponents[(uint32)COMP_TYPE::COLLIDER] = nullptr;
		_vecComponents[(uint32)COMP_TYPE::COLLIDER] = new Collider;
		_vecComponents[(uint32)COMP_TYPE::COLLIDER]->SetOwnerObject(this);
		_vecComponents[(uint32)COMP_TYPE::COLLIDER]->Init();
	}
	
	// Animator ���� ����
	if (other.CheckCompIsValid(COMP_TYPE::ANIMATOR))
	{
		_vecComponents[(uint32)COMP_TYPE::ANIMATOR] = nullptr;
		_vecComponents[(uint32)COMP_TYPE::ANIMATOR] = new Animator;
		_vecComponents[(uint32)COMP_TYPE::ANIMATOR]->SetOwnerObject(this);
		_vecComponents[(uint32)COMP_TYPE::ANIMATOR]->Init();
	}
}

void Object::FinalUpdate()
{
	// ��� ������Ʈ ���̳� ������Ʈ
	for (uint32 i = 0; i < (uint32)COMP_TYPE::END; ++i)
	{
		if (nullptr != _vecComponents[i])
		{
			_vecComponents[i]->Update();
		}
	}
}

void Object::Render()
{
	Rectangle(GET_MEMDC, GetLeft(), GetTop(), GetRight(), GetBottom());

	ComponentRender();
}

void Object::ComponentRender()
{
	for (uint32 i = 0; i < (uint32)COMP_TYPE::END; ++i)
	{
		Component* comp = _vecComponents[i];
		if (nullptr != comp && comp->GetVisibility())
		{
			comp->Render();
		}
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


void Object::Patrol_Vetical_Horizaon_Sin()
{
	//const float _amp = 150.f;		// ����
	//const float _sp = 300.f;		// ���ǵ�

	//auto pos = GetPos();
	//pos.x += float(GetSpeed() * GetDir().x * DT_F);
	//float dis = abs(GetPatrolCenterPos().x - pos.x) - GetPatrolDistance();

	//// y axis -> sin
	//SetAngle(GetAngle() + DT_F * _sp);
	//pos.y = (-1 * float(sin(RAD(GetAngle()))) * _amp) + GetPatrolCenterPos().y;

	//// x�� ������ȯ��
	//if (0.f < dis)
	//{
	//	SetDir(GetDir() * -1);
	//	pos.x += dis * GetDir().x;
	//}

	//// 60�й� ������ 360���� �Ѵ°��
	//if (GetAngle() > 360)
	//{
	//	auto dis = GetAngle() - 360;
	//	SetAngle(GetAngle() - dis);
	//	SetAngle(0);
	//}

	//SetPos(pos);
}

