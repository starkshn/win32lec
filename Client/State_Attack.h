#pragma once
#include "State.h"

class State_Attack : public State
{
public:
	State_Attack();
	virtual ~State_Attack() override;

public:
	virtual void Update() override;

public:
	virtual void StartState()	override;
	virtual void EndState()		override;
};

