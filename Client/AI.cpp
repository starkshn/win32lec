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
	State* s = GetCurState();
	NULL_PTR_CHECK(s);
	GetCurState()->Update();
}

void AI::AddState(State* state)
{
	// if ���ο��� pair��ü�� ������ ����� insert ������ �ʱ�ȭ�� ����ϱ� ������ ���� FindState �Լ��� ���ؼ� nullptrȮ���� �� ���־ �ȴ�?
	if (nullptr == FindState(state->GetState()))
	{
		_mapState.insert({ state->GetState(), state });
		state->SetOwnerAI(this);
	}
}
