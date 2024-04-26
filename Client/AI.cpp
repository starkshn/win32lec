#include "pch.h"
#include "AI.h"
#include "State.h"
#include "Monster.h"

AI::AI()
{

}

AI::~AI()
{
	DeleteResourcesSafe(_mapState);
}

void AI::Update()
{
	NULL_PTR_CHECK(GetCurState());
	GetCurState()->Update();
}

void AI::AddState(State* state)
{
	// if ���ο��� pair��ü�� ������ ����� insert ������ �ʱ�ȭ�� ����ϱ� ������ ���� FindState �Լ��� ���ؼ� nullptrȮ���� �� ���־ �ȴ�.
	if (nullptr == FindState(state->GetState()))
	{
		_mapState.insert({ state->GetState(), GetCurState() });
		state->SetOwnerAI(this);
	}
}
