#pragma once
#include "State.h"

class State_Idle : public State
{
public:
	State_Idle();
	virtual ~State_Idle() override;

public:
	virtual void Update() override;

public:
	virtual void StartState()	override;
	virtual void EndState()		override;
};

