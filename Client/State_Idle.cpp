#include "pch.h"
#include "State_Idle.h"

// �θ��� �⺻ �����ڰ� ���� ������ ��������� �θ��� � �����ڸ� ȣ������ ������ ���־�� �Ѵ�.
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
	// Player ��ġ üũ
	
	// Player�� ���� ���� �ȿ� ������ �����Ѵ�. 
	// Idle ������ ���󼭵� �ٸ��� ������ Idle�� ��ӹ޾Ƽ� ���� �� �ִ�.
}

void State_Idle::StartState()
{

}

void State_Idle::EndState()
{

}
