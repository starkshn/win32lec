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
	// if 내부에서 pair객체를 무조건 만드는 insert 유니폼 초기화를 사용하기 때문에 굳이 FindState 함수를 통해서 nullptr확인을 안 해주어도 된다.
	if (nullptr == FindState(state->GetState()))
	{
		_mapState.insert({ state->GetState(), GetCurState() });
		state->SetOwnerAI(this);
	}
}
