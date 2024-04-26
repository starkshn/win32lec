#include "pch.h"
#include "Monster.h"
#include "Texture.h"
#include "Collider.h"
#include "AI.h"
#include "State.h"
#include "State_Idle.h"
#include "State_Trace.h"

Monster::Monster()
{

}

Monster::~Monster()
{
	DeleteObjectImmediately<AI*>(_moduleAI);
}

void Monster::Update()
{
	UnitObject::Update();
	GetModuleAI()->Update();
}

void Monster::Render()
{
	GameObject::Render();

	uint32 h = (int)GetTexture()->GetTexHeight();
	uint32 w = (int)GetTexture()->GetTexWidth();

	Vec2 pos = GetPos();
	Vec2 renderPos = GetRenderPos();

	int lx = int(renderPos.x - float(w / 2.f));
	int ly = int(renderPos.y - float(h / 2.f));

	TransparentBlt
	(
		GET_MEMDC, 
		int(lx), int(ly), w, h,
		GetTexture()->GetDC(), 
		0, 0, w, h, 
		RGB(255, 0, 255)
	);
}

void Monster::Init()
{
	// name
	SetObjectName(L"DefaultMonster");

	// texture
	SetTexture(static_cast<Texture*>(RESOURCE->LoadTexture(L"Player", L"texture\\test_airplane.bmp")));

	// collider
	Component* comp = CreateComponent<Collider>(COMP_TYPE::COLLIDER);
	int th = GetTexture()->GetTexHeight();
	int tw = GetTexture()->GetTexWidth();
	comp->SetScale(Vec2(GetScale().x - 10.f, GetScale().y - 10.f));
	comp->SetOffset(Vec2(0, 0));

	// Add AI
	{
		AI* ai = new AI();
		State_Idle* idleState = new State_Idle();
		State_Trace* traceState = new State_Trace();
		ai->AddState(idleState);
		ai->AddState(traceState);
		ai->SetCurState(ai->FindState(MONSTER_STATE::IDLE));
		SetModuleAI(ai);
	}
}

void Monster::Begin()
{

}

void Monster::End()
{

}

void Monster::Attack()
{

}

void Monster::OnCollision(Collider* otherCollider)
{
	
}

void Monster::OnCollisionEnter(Collider* otherCollider)
{
	
}

void Monster::OnCollisionExit(Collider* otherCollider)
{

}

void Monster::SetModuleAI(AI* ai)
{
	_moduleAI = ai;
	ai->SetOwner(this);
}
