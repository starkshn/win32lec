#pragma once
#include "State.h"
class State_Move : public State
{
public:
	State_Move();
	virtual ~State_Move() override;

public:
	virtual void Update() override;

public:
	virtual void StartState()	override;
	virtual void EndState()		override;
};

