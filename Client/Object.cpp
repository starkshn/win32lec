#include "pch.h"
#include "Object.h"
#include "Collider.h"

Object::Object()
{
	// 컴포넌트 resize
	_vecComponents.resize((uint32)COMP_TYPE::END);
}

Object::~Object()
{
	// 오브젝트가 들고 있는 모든 컴포넌트 다 Delete
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
	// 위의 _texture의 경우 그냥 얕은 복사를 수행하는데 왜 이렇게 두었을까?
	// Texture클래스는 ResourceManager에서 관리를 하기때문에 얼마든지 얕은 복사를 해도 괜찮다.
	// 깊은 복사를 하는 경우가 더블프리나, 댕글링 포인터 때문에 하는 것인데
	// 메모리 해제를 ResourceManager에서 담당하기 때문에 같은 _texture를 써도 무방하다.

	// Collider 깊은 복사
	if (other.CheckCompIsValid(COMP_TYPE::COLLIDER))
	{
		_vecComponents[(uint32)COMP_TYPE::COLLIDER] = nullptr;
		_vecComponents[(uint32)COMP_TYPE::COLLIDER] = new Collider;
		_vecComponents[(uint32)COMP_TYPE::COLLIDER]->SetOwnerObject(this);
		_vecComponents[(uint32)COMP_TYPE::COLLIDER]->Init();
	}
	
	// Animator 깊은 복사
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
	// 모든 컴포넌트 파이널 업데이트
	for (uint32 i = 0; i < (uint32)COMP_TYPE::END; ++i)
	{
		if (0 < _vecComponents.size() && nullptr != _vecComponents[i])
		{
			_vecComponents[i]->Update();
		}
	}
}

void Object::Render()
{
	SetRenderPos(CAMERA->GetRenderPos(GetPos()));
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

void Object::CheckMouseHoverOnThisObject()
{
	// Get Mouse Render Pos
	Vec2 curMouseRenderPos = RENDER_MOUSE_POS; // current mouse render pos
	Vec2 objRenderPos = GetRenderPos(); // obj render pos

	Vec2 scale = GetScale();
	float objMinX = objRenderPos.x - scale.x / 2.f;
	float objMaxX = objRenderPos.x + scale.x / 2.f;
	float objMinY = objRenderPos.y - scale.y / 2.f;
	float objMaxY = objRenderPos.y + scale.y / 2.f;

	if ((objMinX <= curMouseRenderPos.x && objMaxX >= curMouseRenderPos.x) && (objMinY <= curMouseRenderPos.y && objMaxY >= curMouseRenderPos.y))
	{
		SetMouseHoverOnThisObject(true);

		GetOuterScene()->SetCurMouseHoverObject(this);
		GetOuterScene()->SetCurMouseHoverObjectName(GetObjectName().c_str());
	}
	else
	{
		SetMouseHoverOnThisObject(false);
	}
}

void Object::UpdateMouseInteraction()
{
	CheckMouseHoverOnThisObject();
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
	//const float _amp = 150.f;		// 진폭
	//const float _sp = 300.f;		// 스피드

	//auto pos = GetPos();
	//pos.x += float(GetSpeed() * GetDir().x * DT_F);
	//float dis = abs(GetPatrolCenterPos().x - pos.x) - GetPatrolDistance();

	//// y axis -> sin
	//SetAngle(GetAngle() + DT_F * _sp);
	//pos.y = (-1 * float(sin(RAD(GetAngle()))) * _amp) + GetPatrolCenterPos().y;

	//// x축 방향전환시
	//if (0.f < dis)
	//{
	//	SetDir(GetDir() * -1);
	//	pos.x += dis * GetDir().x;
	//}

	//// 60분법 각도가 360도를 넘는경우
	//if (GetAngle() > 360)
	//{
	//	auto dis = GetAngle() - 360;
	//	SetAngle(GetAngle() - dis);
	//	SetAngle(0);
	//}

	//SetPos(pos);
}

