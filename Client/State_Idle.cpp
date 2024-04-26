#include "pch.h"
#include "State_Idle.h"

// 부모의 기본 생성자가 없기 때문에 명시적으로 부모의 어떤 생성자를 호출할지 결정을 해주어야 한다.
State_Idle::State_Idle()
	:
	State(MONSTER_STATE::IDLE)
{
	
}

State_Idle::~State_Idle()
{
}

void State_Idle::Update()
{
	// Player 위치 체크
	
	// Player가 추적 범위 안에 들어오면 추적한다. 
	// Idle 종류에 따라서도 다르기 때문에 Idle도 상속받아서 만들 수 있다.
}

void State_Idle::StartState()
{

}

void State_Idle::EndState()
{

}
